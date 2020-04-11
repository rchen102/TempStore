package assig3.branch;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.List;

public class Branch {
    private String name;
    private int port;
    private int interval;
    private String ip;
    private int balance;
    private boolean isInit;
    private List<Branch> branches; //List of all other branches

    public Branch(){}

    public Branch(String name, int port, String ip){
        this.name = name;
        this.port = port;
        this.ip = ip;
    }

    public Branch(String name, int port, int interval) {
        this.name = name;
        this.port = port;
        this.interval = interval;
        isInit = false;
    }

    public void start() {
        // start the MsgSender thread
        new Thread(new MsgSender(this, this.interval)).start();

        // start a server listen at port
        try (ServerSocket server = new ServerSocket(this.port)) {
            this.ip = InetAddress.getLocalHost().getHostAddress();
            System.out.println("Server listened at: " + this.ip + ": " + this.port + " \n");
            Socket client = null;
            while (true) {
                // when there is a tcp connection request, start a MsgHandler handle the incoming channel
                client = server.accept();
                new Thread(new MsgHandler(this, client)).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void setName(String name) {
        this.name = name;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public void setInterval(int interval) {
        this.interval = interval;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public void setInit(boolean init) {
        isInit = init;
    }

    public void setBalance(int balance){this.balance = balance;};

    public void setBranches(List<Branch>branches){this.branches = branches;};

    public String getName() {
        return name;
    }

    public int getPort() {
        return port;
    }

    public int getInterval() {
        return interval;
    }

    public String getIp() {
        return ip;
    }

    public int getBalance() {
        return balance;
    }

    public boolean isInit() {
        return isInit;
    }

    public List<Branch> getBranches(){return branches;}

    public boolean withdraw(int value){
        if(this.balance - value < 0)return false;
        else{
            this.balance = this.balance - value;
            return true;
        }
    }

    public void addMoney(int value){
        this.balance+=value;
    }

}
