package assig3.branch;

import assig3.msg.Bank;
import assig3.msg.MsgBuilder;
import assig3.util.MyLogger;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MsgSender {
    private Branch branch;
    private Map<String, Socket> outgoingChannels;
    private Socket controllerSocket;

    MsgSender(Branch branch){
        this.branch = branch;
        outgoingChannels = new HashMap<>();
    }

    public void establishOutgoingChannels(){
        outgoingChannels = new HashMap<>();
        for(Branch b : branch.getBranches()){
            try {
                Socket outgoingSocket = new Socket(b.getIp(),b.getPort());
                outgoingChannels.put(b.getName(),outgoingSocket);

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void startTransfer(int interval){
        new Thread(new SendMoneyThread(this, interval)).start();
    }

    public Branch getBranch() {
        return branch;
    }

    private void sendBranchMsgTo(String branchName, Bank.BranchMessage branchMsg) {
        Socket conn = this.outgoingChannels.get(branchName);
        try {
            OutputStream os = conn.getOutputStream();
            branchMsg.writeDelimitedTo(os);
            // os.close(); // not sure if need close stream
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendTransfer(String randBranch) {
        this.branch.getLock().lock();
        int amount = this.branch.randomTransfer();
        if (amount <= 0) return;
        Bank.BranchMessage branchMessage = MsgBuilder.buildTransfer(this.branch.getName(), amount);
        this.sendBranchMsgTo(randBranch, branchMessage);
        String printMessage = "[Send] "+ amount + " to " + randBranch + ", remain: "+ this.branch.getBalance();
        MyLogger.printMsg(printMessage,2);
        this.branch.getLock().unlock();
    }

    public void sendMarker(int snapShotId, String targetBranchName) throws IOException {
        Bank.BranchMessage markerMessage = MsgBuilder.buildMarker(this.branch.getName(),snapShotId);
        markerMessage.writeDelimitedTo(outgoingChannels.get(targetBranchName).getOutputStream());
        String printMessage = "<SendMarker> id: " + snapShotId + ", to: " + targetBranchName;
        MyLogger.printMsg(printMessage,1);
    }

    public void sendReturnSnapshot(int snapShotId, List<Integer> record,int balance) throws IOException {
        Bank.BranchMessage returnMessage = MsgBuilder.buildReturnSnapshot(snapShotId,record,balance);
        returnMessage.writeDelimitedTo(controllerSocket.getOutputStream());
        String printMessage = ("<SendReturnSnapshot> id: " + snapShotId);
        MyLogger.printMsg(printMessage,1);
    }

    public Map<String, Socket> getOutgoingChannels() {
        return outgoingChannels;
    }

    public void setControllerSocket(Socket controllerSocket) {
        this.controllerSocket = controllerSocket;
    }
}


