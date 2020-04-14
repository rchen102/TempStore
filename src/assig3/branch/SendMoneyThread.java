package assig3.branch;


import java.util.List;
import java.util.Random;

public class SendMoneyThread implements Runnable {
    private MsgSender msgSender;
    private int interval;
    private List<Branch> branches;

    public SendMoneyThread(MsgSender msgSender, int interval) {
        this.interval = interval;
        this.msgSender = msgSender;
        this.branches = this.msgSender.getBranch().getBranches();
    }

    @Override
    public void run() {
        try {
            while(true){
                String randBranch = getRandBranch();
                this.msgSender.sendTransfer(randBranch);
                Thread.sleep(getRandInterval());
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public String getRandBranch(){
        //select Random Branch;
        int size = this.branches.size();
        Random rand = new Random();
        int randBranch = rand.nextInt(size);
        return this.branches.get(randBranch).getName();
    }

    public int getRandInterval(){
        Random rand = new Random();
        return rand.nextInt(this.interval+1);
    }
}
