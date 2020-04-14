package assig3.branch;

import assig3.msg.Bank;
import assig3.util.MyLogger;

import java.io.IOException;

public class MsgHandler {
    private Branch branch;

    public MsgHandler(Branch branch) {
        this.branch = branch;
    }

    // Each time, only handle one msg
    public void handle(Bank.BranchMessage branchMessage) throws IOException {
        this.branch.getLock().lock();
        if (branchMessage.hasTransfer()) {
            this.handleTransfer(branchMessage);
        }
        else if (branchMessage.hasInitSnapshot()) {
            this.handleInitSnapshot(branchMessage);
        }
        else if (branchMessage.hasMarker()) {
            this.handleMarker(branchMessage);
        }
        else if (branchMessage.hasRetrieveSnapshot()) {
            this.handleRetrieveSnapshot(branchMessage);
        }
        this.branch.getLock().unlock();
    }

    public synchronized void handleTransfer(Bank.BranchMessage branchMessage){
        int amount = branchMessage.getTransfer().getAmount();
        int old = branch.getBalance();
        branch.addMoney(amount,branchMessage.getTransfer().getSendBranch());
        String printMessage = ("[Receive] " + amount + " from " + branchMessage.getTransfer().getSendBranch() + ", now: " + branch.getBalance());
        MyLogger.printMsg(printMessage,2);
    }

    public synchronized void handleInitSnapshot(Bank.BranchMessage branchMessage) throws IOException {
        int snapshotId = branchMessage.getInitSnapshot().getSnapshotId();
        String printMessage = "<InitSnapshot> id: " + snapshotId;
        MyLogger.printMsg(printMessage,1);
        branch.handleInitSnapshot(snapshotId);
    }

    public synchronized void handleMarker(Bank.BranchMessage branchMessage) throws IOException {
        int snapShotId = branchMessage.getMarker().getSnapshotId();
        String sender = branchMessage.getMarker().getSendBranch();
        // If the id has already in the list, means the marker message sees before
        String printMessage = "<Marker> id: " + snapShotId + ", from: " + sender;
        MyLogger.printMsg(printMessage,1);
        branch.handleMarker(snapShotId, sender);
    }

    public synchronized void handleRetrieveSnapshot(Bank.BranchMessage branchMessage) throws IOException {
        int snapshotId = branchMessage.getRetrieveSnapshot().getSnapshotId();
        String printMessage = "<RetrieveSnapshot> id: " + snapshotId;
        MyLogger.printMsg(printMessage,1);
        branch.handleRetrieveSnapshot(snapshotId);
    }


}
