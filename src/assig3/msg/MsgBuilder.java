package assig3.msg;

import assig3.branch.Branch;

import java.util.List;

public class MsgBuilder {
    public static Bank.BranchMessage buildInitBranch(int balance, List<Branch> branches) {
        Bank.BranchMessage.Builder branchMsg = Bank.BranchMessage.newBuilder();
        Bank.InitBranch.Builder initBranch = Bank.InitBranch.newBuilder();
        initBranch.setBalance(balance);
        for (Branch branchIn : branches) {
            initBranch.addAllBranches(Translator.toMsgBranch(branchIn));
        }
        branchMsg.setInitBranch(initBranch.build());
        return branchMsg.build();
    }

    public static Bank.BranchMessage buildTransfer(String sendBranch, int amount) {
        Bank.BranchMessage.Builder branchMsg = Bank.BranchMessage.newBuilder();
        Bank.Transfer.Builder transfer = Bank.Transfer.newBuilder();
        transfer.setSendBranch(sendBranch);
        transfer.setAmount(amount);
        branchMsg.setTransfer(transfer.build());
        return branchMsg.build();
    }

    public static Bank.BranchMessage buildInitSnapshot(int snapshotId) {
        Bank.BranchMessage.Builder branchMsg = Bank.BranchMessage.newBuilder();
        Bank.InitSnapshot.Builder initSnapshot = Bank.InitSnapshot.newBuilder();
        initSnapshot.setSnapshotId(snapshotId);
        branchMsg.setInitSnapshot(initSnapshot.build());
        return branchMsg.build();
    }

    public static Bank.BranchMessage buildMarker(String sendBranch, int snapshotId) {
        Bank.BranchMessage.Builder branchMsg = Bank.BranchMessage.newBuilder();
        Bank.Marker.Builder marker = Bank.Marker.newBuilder();
        marker.setSendBranch(sendBranch);
        marker.setSnapshotId(snapshotId);
        branchMsg.setMarker(marker.build());
        return branchMsg.build();
    }

    public static Bank.BranchMessage buildRetrieveSnapshot(int snapshotId) {
        Bank.BranchMessage.Builder branchMsg = Bank.BranchMessage.newBuilder();
        Bank.RetrieveSnapshot.Builder retrieveSnapshot = Bank.RetrieveSnapshot.newBuilder();
        retrieveSnapshot.setSnapshotId(snapshotId);
        branchMsg.setRetrieveSnapshot(retrieveSnapshot.build());
        return branchMsg.build();
    }

    public static Bank.BranchMessage buildReturnSnapshot() {
        Bank.BranchMessage.Builder branchMsg = Bank.BranchMessage.newBuilder();
        // TODO wait until snapshot related part done
        return  branchMsg.build();
    }
}
