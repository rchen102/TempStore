package assig3.controller;

import assig3.branch.Branch;

import java.util.List;
import java.util.Random;

public class SnapshotProxyThread implements Runnable {
    private MsgSender msgSender;
    private int globalSnapshotId;

    public SnapshotProxyThread(MsgSender msgSender) {
        this.msgSender = msgSender;
        this.globalSnapshotId = 0;
    }

    @Override
    public void run() {
        while (true) {
            try {
                int id = this.nextId();
                String branchName = this.getRandBranch();
                this.msgSender.sendInitSnapshot(branchName, id);
                Thread.sleep(5000L);
                this.msgSender.sendRetrieveSnapshot(id);
                this.msgSender.getController().snapshotCollector.printSnapshot();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private String getRandBranch(){
        List<Branch> branches = this.msgSender.getController().getBranches();
        Random rand = new Random();
        int randBranch = rand.nextInt(branches.size());
        return branches.get(randBranch).getName();
    }

    private int nextId() {
        int id = this.globalSnapshotId;
        this.globalSnapshotId++;
        return id;
    }
}
