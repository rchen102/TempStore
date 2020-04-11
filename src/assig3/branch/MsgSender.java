package assig3.branch;


import assig3.msg.Bank;
import assig3.msg.MsgBuilder;

import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;
import java.util.*;

public class MsgSender implements Runnable {
    private Branch branch;
    private int interval;
    private List<Socket> outgoingChannels;

    public MsgSender(Branch branch, int interval) {
        this.branch = branch;
        this.interval = interval;
    }

    public void StartTransfer() throws IOException {
        int balance = branch.getBalance();
        int transferAmount = 0;

        double randPercentage = getRandPercentage();
        int randBranch = getRandBranch(branch.getBranches().size());

       // Bank.Transfer.Builder transferMsgBuilder = Bank.Transfer.newBuilder();

        //1: calculate amount for transfer
        //2: wrap up transfer message
        //3: get target socket from randomly selected branch in all out going channels
        //4: decrease self balance then send out the transfer message
        transferAmount = (int)(balance*randPercentage);
        //System.out.println("Random percentage: "+randPercentage + ", Random branch: "+ randBranch);

        if(branch.withdraw(transferAmount)){
            Bank.BranchMessage branchMessage = MsgBuilder.buildTransfer(branch.getName(),transferAmount);
            System.out.println("[Send] "+ transferAmount+", "+branch.getBranches().get(randBranch).getName()+", "+balance+", "+branch.getBalance());
            branchMessage.writeDelimitedTo(outgoingChannels.get(randBranch).getOutputStream());
        }
        else{
            System.out.println("Transfer amount greater than balance, invalid transaction, abort!");
        }

    }
    public double getRandPercentage(){
        int min = 50;
        int max = 100;

        //Transfer random amount of money, in range of [0.05,0.10]
        //Check before transfer, transfer amount is round up!
        double randPercentage = Math.random()*((max-min)+1)+min;
        return randPercentage/1000;
    }

    public int getRandBranch(int size){
        //select Random Branch;
        Random rand = new Random();
        int randBranch = rand.nextInt(branch.getBranches().size());
        return randBranch;
    }

    public void establishOutgoingChannels(){
        outgoingChannels = new ArrayList<>();
        for(Branch branch : branch.getBranches()){
            try {
                Socket outgoingSocket = new Socket(branch.getIp(),branch.getPort());
                outgoingChannels.add(outgoingSocket);

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    @Override
    public void run() {
        while(!branch.isInit())
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("sender awake,establish out going channels");

        establishOutgoingChannels();

        System.out.println("Sender start transfer");
        try {
            StartTransfer();
        } catch (IOException e) {
            e.printStackTrace();
        }


    }
}
