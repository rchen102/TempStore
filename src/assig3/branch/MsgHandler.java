package assig3.branch;

import assig3.msg.Bank;
import assig3.msg.Translator;

import javax.sound.midi.Soundbank;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class MsgHandler implements Runnable {
    private Branch branch;
    private Socket client;

    public MsgHandler(Branch branch, Socket client) {
        this.branch = branch;
        this.client = client;
    }
    public void handle(Bank.BranchMessage branchMessage) {

        if (branchMessage.hasInitBranch()) {
            handleInitBranch(branchMessage);
        } else if (branchMessage.hasInitSnapshot()) {
            //do something to initSnapshot
            handleInitSnapshot();
        } else if (branchMessage.hasRetrieveSnapshot()) {
            //do
            handleRetrieveSnapshot();
        } else if (branchMessage.hasReturnSnapshot()) {
            //do
            handleReturnSnapshot();
        } else if (branchMessage.hasTransfer()) {
            handleTransfer(branchMessage);

        } else if (branchMessage.hasMarker()) {
            handleMarker();
        }
    }

    public void handleInitBranch(Bank.BranchMessage branchMessage){
        System.out.println("Received Initial Message From Controller");
        branch.setInit(true);
        branch.setBalance(branchMessage.getInitBranch().getBalance());
        branch.setBranches(filter(Translator.bankBranchToBranch(branchMessage.getInitBranch().getAllBranchesList())));
        System.out.println("<InitialBranch> Initial balance = "+ branch.getBalance() + ",Size of branches: "+branch.getBranches().size());

    }

    public List<Branch>filter(List<Branch>branches){
        List<Branch> res = new ArrayList<>();
        for(Branch b : branches){
            if(b.getName().equals(branch.getName())){
                continue;
            }
            else res.add(b);
        }
        return res;
    }

    public void handleTransfer(Bank.BranchMessage branchMessage){
        int amount = branchMessage.getTransfer().getAmount();
        int old = branch.getBalance();
        branch.addMoney(amount);
        System.out.println("[Receive]: " + amount + ", " + branchMessage.getTransfer().getSendBranch() + ", "
                + old + ", " + branch.getBalance());
    }

    public void handleInitSnapshot(){

    }

    public void handleRetrieveSnapshot(){}

    public void handleReturnSnapshot(){

    }

    public void handleMarker(){

    }
    @Override
    public void run() {
        try {
            InputStream inputStream = client.getInputStream();
            Bank.BranchMessage branchMessage = null;
            while( (branchMessage = Bank.BranchMessage.parseDelimitedFrom(inputStream)) != null) {
                handle(branchMessage);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
