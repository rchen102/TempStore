package assig3.branch;

import assig3.util.MyLogger;

public class BranchDriver {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Please give 3 parameters");
            System.exit(-1);
        }
        String name = args[0];
        int port = Integer.valueOf(args[1]);
        int interval = Integer.valueOf(args[2]);
        if(interval <= 1000){
            MyLogger.setLoggerLevel(3);
        }
        else{
            MyLogger.setLoggerLevel(2);
        }
        MyLogger.setLoggerLevel(1);
        String printMessage = "name = " + name + ", port = " + port + ", interval = " + interval;
        MyLogger.printMsg(printMessage,1);
        Branch branch = new Branch(name, port, interval);
        branch.start();
    }
}
