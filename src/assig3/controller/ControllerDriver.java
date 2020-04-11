package assig3.controller;

public class ControllerDriver {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please input 2 parameters");
            System.exit(-1);
        }
        int totalMoney = Integer.valueOf(args[0]);
        String filename = args[1];
        System.out.println("Total money = " + totalMoney + ", filename = " + filename);
        Controller controller = new Controller(totalMoney, filename);
        controller.start();
    }
}
