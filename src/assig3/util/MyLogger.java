package assig3.util;

public class MyLogger {
    private static int debugLevel;
    //1: no printing
    //2: print all receiving transfer
    public static void setLoggerLevel (int level ){
        debugLevel = level;
    }

    public static void printMsg (String message, int level ){
        if(level >= debugLevel){
            System.out.println(message);
        }
    }

}


