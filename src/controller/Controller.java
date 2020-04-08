package controller;

public class Controller {
    public static int total;
    public static String filename;

    public static void main(String[] args) {
        total = Integer.valueOf(args[0]);
        filename = args[1];
        System.out.println("Total money = " + total + ", filename = " + filename);
    }
}
