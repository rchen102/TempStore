package assig3.controller;

import assig3.branch.Branch;
import assig3.util.FileProcessor;

import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Controller {
    private int totalMoney;
    private String filename;
    private List<Branch> branches;
    private MsgSender msgSender;

    public SnapshotCollector snapshotCollector;

    public Controller(int totalMoney, String filename) {
        this.totalMoney = totalMoney;
        this.filename = filename;
    }

    public void start() {
        // 1. read branch list from file
        this.initBranchList();

        // 2. establish duplex connection and start MsgSender, MsgHandler
        this.msgSender = new MsgSender(this);
        this.msgSender.establishConn();
        this.startMsgHandlers(this.msgSender.getConnMap());

        // send InitBranch
        this.msgSender.sendInitBranch();

        // start to collect global Snapshots
        this.snapshotCollector = new SnapshotCollector(this.branches.size());
        this.msgSender.startCollectGlobalSnapshot();
    }

    private void startMsgHandlers(Map<String, Socket> connMap) {
        connMap.forEach((branchName, socket) -> {
            new Thread(new MsgHandler(this, branchName, socket)).start();
        });
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
            this.branches.add(new Branch(name, ip, port));
        }
        fp.closeScanner();
    }

    public List<Branch> getBranches() {
        return branches;
    }

    public int getTotalMoney() {
        return totalMoney;
    }
}
