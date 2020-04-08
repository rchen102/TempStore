package assig3.branch;

public class Branch {
    public static String name;
    public static int interval;
    public static int port;

    public static void main(String[] args) {
        name = args[0];
        port = Integer.valueOf(args[1]);
        interval = Integer.valueOf(args[2]);
        System.out.println("name = " + name + ", port = " + port + ", interval = " + interval);
    }
}
