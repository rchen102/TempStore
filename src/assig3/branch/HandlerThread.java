package assig3.branch;

import assig3.msg.Bank;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;

public class HandlerThread implements Runnable {
    private MsgHandler handler;
    private Socket client;

    public HandlerThread(MsgHandler handler, Socket client) {
        this.handler = handler;
        this.client = client;
    }

    @Override
    public void run() {
        try {
            InputStream inputStream = client.getInputStream();
            Bank.BranchMessage branchMessage = null;
            while( (branchMessage = Bank.BranchMessage.parseDelimitedFrom(inputStream)) != null) {
                this.handler.handle(branchMessage);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
