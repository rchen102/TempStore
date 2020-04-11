package assig3.branch;

public class BranchDriver {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Please give 3 parameters");
            System.exit(-1);
        }
        String name = args[0];
        int port = Integer.valueOf(args[1]);
        int interval = Integer.valueOf(args[2]);
        System.out.println("name = " + name + ", port = " + port + ", interval = " + interval);
        Branch branch = new Branch(name, port, interval);
        branch.start();
    }
}
