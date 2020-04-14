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
    }

    public void printSnapshot() {
        if (!this.snapshotMap.containsKey(this.globalSnapshotId)) return;
        List<Snapshot> snapshots = this.snapshotMap.get(globalSnapshotId);
        int size = snapshots.size();
        if (size == requiredSize) {
            MyLogger.printMsg("snapshot_id: " + this.globalSnapshotId, 2);
            for (Snapshot sp : snapshots) {
                MyLogger.printMsg(sp.toString(), 2);
            }
            this.globalSnapshotId++;
        }
        //TODO remove snapshot id
    }
}
