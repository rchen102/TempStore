package assig3.controller;

import assig3.msg.Bank;
import assig3.util.MyLogger;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.List;

public class MsgHandler implements Runnable {
    private Controller controller;
    private String branchName;
    private Socket client;

    public MsgHandler(Controller controller, String branchName, Socket client) {
        this.controller = controller;
        this.branchName = branchName;
        this.client = client;
    }

    @Override
    public void run() {
        try {
            MyLogger.printMsg("MsgHandler for " + this.branchName + " start", 1);
            while(true) {
                InputStream inputStream = client.getInputStream();
                Bank.BranchMessage branchMessage = Bank.BranchMessage.parseDelimitedFrom(inputStream);
                handle(branchMessage);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void handle(Bank.BranchMessage branchMessage) {
        if (branchMessage == null) return;
        if (!branchMessage.hasReturnSnapshot()) {
            System.err.println("Receive non-targeted msg, only handle ReturnSnapshot");
            return;
        }
        Bank.ReturnSnapshot.LocalSnapshot localSnapshot = branchMessage.getReturnSnapshot().getLocalSnapshot();
        int snapshotId = localSnapshot.getSnapshotId();
        int balance = localSnapshot.getBalance();
        List<Integer> channelState = localSnapshot.getChannelStateList();
        Snapshot sp = new Snapshot(this.branchName, balance, channelState, this.controller.getBranches());

        this.controller.snapshotCollector.addLocalSnapshot(snapshotId, sp);
        MyLogger.printMsg("[ReturnSnapshot] from " + this.branchName + ", id " + snapshotId, 1);
    }
}
