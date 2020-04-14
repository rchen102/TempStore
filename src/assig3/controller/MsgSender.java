package assig3.controller;

import assig3.branch.Branch;
import assig3.msg.Bank;
import assig3.msg.MsgBuilder;
import assig3.util.MyLogger;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

public class MsgSender {
    private Controller controller;
    private Map<String, Socket> connMap;

    public MsgSender(Controller controller) {
        this.controller = controller;
        this.connMap = new HashMap<>();
    }

    public void establishConn() {
        String name;
        String ip;
        int port;
        Socket socket;
        for (Branch branch : this.controller.getBranches()) {
            name = branch.getName();
            ip = branch.getIp();
            port = branch.getPort();
            try {
                socket = new Socket(ip, port);
                this.connMap.put(name, socket);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        MyLogger.printMsg("TCP connections established", 1);
    }

    public void startCollectGlobalSnapshot() {
        new Thread(new SnapshotCollectingThread(this)).start();
        MyLogger.printMsg("Start collect global snapshots", 1);
    }

    private void sendBranchMsgTo(String branchName, Bank.BranchMessage branchMsg) {
        Socket conn = this.connMap.get(branchName);
        try {
            OutputStream os = conn.getOutputStream();
            branchMsg.writeDelimitedTo(os);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void sendBranchMsgToAll(Bank.BranchMessage branchMsg) {
        for (String branchName : this.connMap.keySet()) {
            this.sendBranchMsgTo(branchName, branchMsg);
        }
    }

    public void sendInitBranch() {
        int balance = this.controller.getTotalMoney() / this.controller.getBranches().size();
        Bank.BranchMessage branchMsg = MsgBuilder.buildInitBranch(balance, this.controller.getBranches());
        this.sendBranchMsgToAll(branchMsg);
        MyLogger.printMsg("[InitBranch] balance: " + balance, 1);
    }

    public void sendInitSnapshot(String branchName, int snapshotId) {
        Bank.BranchMessage branchMsg = MsgBuilder.buildInitSnapshot(snapshotId);
        this.sendBranchMsgTo(branchName, branchMsg);
        MyLogger.printMsg("[InitSnapshot] to: " + branchName + ", id: " + snapshotId, 1);
    }

    public void sendRetrieveSnapshot(int snapshotId) {
        Bank.BranchMessage branchMsg = MsgBuilder.buildRetrieveSnapshot(snapshotId);
        this.sendBranchMsgToAll(branchMsg);
        MyLogger.printMsg("[RetrieveSnapshot] to all, id: " + snapshotId, 1);
    }

    public Controller getController() {
        return controller;
    }

    public Map<String, Socket> getConnMap() {
        return this.connMap;
    }
}
