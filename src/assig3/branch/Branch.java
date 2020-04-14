package assig3.branch;

import assig3.msg.Bank;
import assig3.msg.Translator;

import java.io.IOException;
import java.io.InputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Branch {
    private String name;
    private int port;
    private int interval;
    private String ip;
    private int balance;

    private Lock lock = new ReentrantLock();

    private MsgSender msgSender;
    private List<Branch> branches = null;
    public List<Integer> snapshotList = new ArrayList<>();
    public Map<Integer,Map<String, Boolean>> channelWorkState = new HashMap<>();
    public Map<Integer,Map<String, Integer>> channelRecord = new HashMap<>();
    public Map<Integer,Integer> localStateBalance = new HashMap<>();

    public Branch(){}

    public Branch(String name, int port, int interval) {
        this.name = name;
        this.port = port;
        this.interval = interval;
    }

    public Branch(String name, String ip, int port) {
        this.name = name;
        this.ip = ip;
        this.port = port;
    }

    public void start() {
        msgSender = new MsgSender(this);
        try (ServerSocket server = new ServerSocket(this.port)) {
            this.ip = InetAddress.getLocalHost().getHostAddress();
            System.out.println("Server listened at: " + this.ip + ": " + this.port + " \n");
            Socket controllerClient = server.accept();

            // Handle InitBranch
            InputStream inputStream = controllerClient.getInputStream();
            Bank.BranchMessage branchMessage = Bank.BranchMessage.parseDelimitedFrom(inputStream);
            if (!branchMessage.hasInitBranch()) {
                System.err.println("Receive other msg before initialization.");
                return;
            }
            Bank.InitBranch initBranch = branchMessage.getInitBranch();
            this.balance = initBranch.getBalance();
            this.setBranches(Translator.bankBranchToBranch(initBranch.getAllBranchesList()));
            Handler handler = new Handler(this);
            new Thread(new MsgHandler(handler, controllerClient)).start();

            // Wait for other branch to connect
            this.msgSender.setControllerSocket(controllerClient);
            this.msgSender.establishOutgoingChannels();
            int numOfConn = 0;
            while (numOfConn != this.branches.size()) {
                Socket client = server.accept();
                numOfConn++;
                System.out.println("conn established!");
                new Thread(new MsgHandler(handler, client)).start();
            }

            // Start transfer money
            System.out.println("main end, conn #: " + numOfConn);
            this.msgSender.startTransfer(this.interval);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void setBranches(List<Branch> branches) {
        this.branches = new ArrayList<>();
        for(Branch branch : branches){
            if(branch.getName().equals(this.name)) continue;
            else this.branches.add(branch);
        }
    }

    private void initLocalSnapshotVar(int snapshotId) {
        this.snapshotList.add(snapshotId);
        Map<String, Boolean> tmpState = new HashMap<>();
        Map<String, Integer> tmpRecord = new HashMap<>();
        for (Branch branch : branches) {
            tmpState.put(branch.getName(), false);
            tmpRecord.put(branch.getName(), 0);
        }
        this.channelWorkState.put(snapshotId, tmpState);
        this.channelRecord.put(snapshotId, tmpRecord);
    }

    public void handleInitSnapshot(int snapShotId) throws IOException {
        //1: Record own state
        this.localStateBalance.put(snapShotId, this.balance);

        //2: Start to record incoming channels and send marker to all other branches
        this.initLocalSnapshotVar(snapShotId);
        for(Branch b : branches) {
            channelWorkState.get(snapShotId).put(b.getName(),true);
            this.msgSender.sendMarker(snapShotId, b.getName());
        }
    }

    public void handleMarker(int snapShotId, String sender) throws IOException {
        // See the marker before
        if(this.snapshotList.contains(snapShotId)){
           // System.out.println("See the marker before");
            if(this.channelWorkState.get(snapShotId).get(sender)){
                //System.out.println("<Marker> see before, close"+ sender);
                channelWorkState.get(snapShotId).put(sender,false);
            }
        }
        else{
            // First time see the marker
            //1: Record own state
            this.localStateBalance.put(snapShotId, this.balance);

            //2: Start to record incoming channels and send marker to all other branches
            this.initLocalSnapshotVar(snapShotId);
            for(Branch b : branches){
                if (!b.getName().equals(sender)) {
                    channelWorkState.get(snapShotId).put(b.getName(),true);
                }
                msgSender.sendMarker(snapShotId,b.getName());
            }
        }
    }

    public void handleRetrieveSnapshot(int snapShotId) throws IOException {
        List<Integer> res = new ArrayList<>();
        Map<String,Integer> tempMap = this.channelRecord.get(snapShotId);
        for(Branch b : branches){
            int temp = tempMap.get(b.getName());
            res.add(temp);
        }
        msgSender.sendReturnSnapshot(snapShotId,res,this.localStateBalance.get(snapShotId));

        //remove the snapshotId
        this.snapshotList.remove(new Integer(snapShotId));
        this.channelRecord.remove(snapShotId);
        this.channelWorkState.remove(snapShotId);
    }

    public int randomTransfer() {
        double ratio = getRandPercentage();
        int amount = (int)(this.balance * ratio);
        if (this.withdraw(amount)) return amount;
        return 0;
    }

    private double getRandPercentage(){
        int min = 50;
        int max = 100;
        //Transfer random amount of money, in range of [0.05,0.10]
        //Check before transfer, transfer amount is round up!
        double randPercentage = Math.random()*((max-min)+1)+min;
        return randPercentage/1000;
    }

    public boolean withdraw(int value){
        value = -value;
        return this.updateBalance(value);
    }

    public synchronized void addMoney(int value,String senderName){
        this.balance += value;
        for(Integer s : snapshotList) {
            if (this.channelWorkState.get(s).get(senderName)) {
                int before = this.channelRecord.get(s).get(senderName);
                int after = before + value;
                this.channelRecord.get(s).put(senderName, after);
                //System.out.println("<Snapshot:received incoming> snapShotId: " + s + " from: " + senderName + " Before: " + before + " After:" + after);
            }
        }
    }

    private synchronized boolean updateBalance(int value) {
        if (value >= 0) {
            this.balance += value;
        }
        else {
            if(this.balance + value < 0) return false;
            this.balance += value;
        }
        return true;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public String getName() {
        return name;
    }

    public int getPort() {
        return port;
    }

    public String getIp() {
        return ip;
    }

    public synchronized int getBalance() {
        return balance;
    }

    public List<Branch> getBranches(){return branches;}

    public Lock getLock() {
        return lock;
    }
}
