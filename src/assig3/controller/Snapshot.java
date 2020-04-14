package assig3.controller;

import assig3.branch.Branch;

import java.util.List;

public class Snapshot {
    private String branchName;
    private int balance;
    private List<Integer> channelState;
    private List<Branch> branches;

    public Snapshot(String branchName, int balance, List<Integer> channelState, List<Branch> branches) {
        this.branchName = branchName;
        this.balance = balance;
        this.channelState = channelState;
        this.branches = branches;
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(this.branchName + ": " + this.balance);
        int ptr = 0;
        for (Branch branch : branches) {
            if (branch.getName().equals(this.branchName)) continue;
            sb.append(", " + branch.getName() + "->" + this.branchName + ": " + this.channelState.get(ptr));
            ptr++;
        }
        return sb.toString();
    }
}
