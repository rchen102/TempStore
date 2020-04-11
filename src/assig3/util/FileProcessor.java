package assig3.util;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class FileProcessor {
    private Scanner sc = null;
    private FileWriter fw = null;

    public void setWriter(String fileName) {
        try {
            this.fw = new FileWriter(new File(fileName));
        }
        catch (IOException e){
            System.err.println("Error occurred while creating writer.");
            e.printStackTrace();
            System.exit(0);
        }

    }

    public void closeWriter() {
        try {
            if (this.fw != null) this.fw.close();
        }
        catch (IOException e){
            System.err.println("Error occurred while close writer.");
            e.printStackTrace();
            System.exit(0);
        }

    }

    public void writeOneLine(String line) {
        try {
            this.fw.write(line);
        }
        catch (IOException e){
            System.err.println("Error occurred while writing file.");
            e.printStackTrace();
            System.exit(0);
        }
    }

    public void setScanner(String fileName) {
        if (this.sc != null) {
            this.sc.close();
            this.sc = null;
        }
        try {
            this.sc = new Scanner(new File(fileName));
        }
        catch (FileNotFoundException e) {
            System.err.println("Error: File '" + fileName + "' not found.");
            System.err.println("Please check fileName and correct directory to place file.");
            e.printStackTrace();
            System.exit(0);
        }
        finally {
        }
    }

    public boolean hasNext() {
        if (this.sc == null) return false;
        return this.sc.hasNext();
    }

    public String readOneLine() {
        if (!this.hasNext()) return "";
        return this.sc.nextLine();
    }

    public void closeScanner() {
        if (this.sc != null) this.sc.close();
    }

    public void writeFileAppend(String fileName, String str) {
        try (FileWriter fw = new FileWriter(new File(fileName), true)) {
            fw.write(str);
        }
        catch (IOException e){
            System.err.println("Error occurred while writing file.");
            e.printStackTrace();
            System.exit(0);
        }
        finally {
        }
    }

    public String toString() {
        return "FileProcessor";
    }
}
