package assig3.controller;

import assig3.branch.Branch;
import assig3.msg.Bank;
import assig3.msg.MsgBuilder;
import assig3.util.FileProcessor;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.HashMap;

public class Controller {
    private int totalMoney;
    private String filename;
    private List<Branch> branches;
    private Map<String, Socket> connMap;  // <k: branchName, v: tcp conn>

    public Controller(int totalMoney, String filename) {
        this.totalMoney = totalMoney;
        this.filename = filename;
    }

    public void start() {
        this.initBranchList();
        this.establishConn();
        this.sendInitBranch();
    }

    private void initBranchList() {
        this.branches = new ArrayList<>();
        FileProcessor fp = new FileProcessor();
        fp.setScanner(filename);
        while (fp.hasNext()) {
            String line = fp.readOneLine();
            String[] branchInfo = line.split(" ");
            if (branchInfo.length < 3) continue;
            String name = branchInfo[0];
            String ip = branchInfo[1];
            int port = Integer.parseInt(branchInfo[2]);
            this.branches.add(new Branch(name, port, ip));
        }
        fp.closeScanner();
    }

    private void establishConn() {
        this.connMap = new HashMap<>();
        String name;
        String ip;
        int port;
        Socket socket;
        for (Branch branch : branches) {
            name = branch.getName();
            ip = branch.getIp();
            port = branch.getPort();
            try {
               socket = new Socket(ip, port);
               this.connMap.put(name, socket);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void sendInitBranch() {
        int balance = this.totalMoney / this.branches.size();
        Bank.BranchMessage branchMsg = MsgBuilder.buildInitBranch(balance, this.branches);
        for (Socket conn : this.connMap.values()) {
            try {
                OutputStream os = conn.getOutputStream();
                branchMsg.writeDelimitedTo(os);
                // os.close(); // not sure if need close stream
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
