package assig3.controller;

import assig3.util.MyLogger;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class SnapshotCollector {
    private int requiredSize;
    private int globalSnapshotId;
    private Map<Integer, List<Snapshot>> snapshotMap;

    public SnapshotCollector(int requiredSizesize) {
        this.globalSnapshotId = 0;
        this.requiredSize = requiredSizesize;
        this.snapshotMap = new HashMap<>();
    }

    public synchronized void addLocalSnapshot(int snapshotId, Snapshot snapshot) {
        List<Snapshot> list;
        if (!this.snapshotMap.containsKey(snapshotId)) list = new ArrayList<>();
        else list = this.snapshotMap.get(snapshotId);
        list.add(snapshot);
        this.snapshotMap.put(snapshotId, list);
        //System.out.println("<< id: " + snapshotId + " added>>");
    }

    public void printSnapshot() {
        boolean tmp = this.snapshotMap.containsKey(this.globalSnapshotId);
       // System.out.println("check for id: " + this.globalSnapshotId + ", " + tmp);
        if (!tmp) {
           // System.out.println("not exist yet, end");
            return;
        }
        List<Snapshot> snapshots = this.snapshotMap.get(globalSnapshotId);
        int size = snapshots.size();
      //  System.out.println("Exist, check #: " + size + ", req: " + requiredSize);
        if (size == requiredSize) {
            MyLogger.printMsg("snapshot_id: " + this.globalSnapshotId, 2);
            for (Snapshot sp : snapshots) {
                MyLogger.printMsg(sp.toString(), 2);
            }
            this.globalSnapshotId++;
       //     System.out.println("new id: " + this.globalSnapshotId);
        }
    }

    public synchronized void showSnapshot() {
        List<Integer> datedId = new ArrayList<>();
        this.snapshotMap.forEach((id, snapshots) -> {
            if (snapshots.size() == requiredSize) {
                MyLogger.printMsg("snapshot_id: " + id, 2);
                for (Snapshot sp : snapshots) {
                    MyLogger.printMsg(sp.toString(), 2);
                }
                datedId.add(id);
            }
        });
        // remove snapshot that has already been printed
        for (int id : datedId) {
            this.snapshotMap.remove(id);
        }
    }
}
