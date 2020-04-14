package assig3.controller;

import assig3.util.MyLogger;

public class ControllerDriver {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please input 2 parameters");
            System.exit(-1);
        }
        int totalMoney = Integer.valueOf(args[0]);
        String filename = args[1];
        MyLogger.setLoggerLevel(2);
        MyLogger.printMsg("Total money = " + totalMoney + ", filename = " + filename, 1);
        Controller controller = new Controller(totalMoney, filename);
        controller.start();
    }
}
