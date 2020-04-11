package assig3.msg;

import assig3.branch.Branch;

import java.util.ArrayList;
import java.util.List;

public class Translator {
    public static List<Branch> bankBranchToBranch(List<Bank.InitBranch.Branch> branches){
        List<Branch> res = new ArrayList<Branch>();
        int size = branches.size();
        for (Bank.InitBranch.Branch branch : branches) {
            Branch temp = new Branch();
            temp.setIp(branch.getIp());
            temp.setName(branch.getName());
            temp.setPort(branch.getPort());
            res.add(temp);

        }
        return res;
    }

    public static Bank.InitBranch.Branch toMsgBranch(Branch branchIn) {
        Bank.InitBranch.Branch.Builder branch = Bank.InitBranch.Branch.newBuilder();
        branch.setName(branchIn.getName());
        branch.setIp(branchIn.getIp());
        branch.setPort(branchIn.getPort());
        return branch.build();
    }

    public static Branch toBranch(Bank.InitBranch.Branch branchIn) {
        Branch branch = new Branch();
        branch.setName(branchIn.getName());
        branch.setIp(branchIn.getIp());
        branch.setPort(branchIn.getPort());
        return branch;
    }
}
