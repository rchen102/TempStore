package assig3.util;
/**
 * For Branch:
 * <= 1000, Logger.setDebugLevel(3)
 * > 1000, only want to see send/receive, Logger.setDebugLevel(2)
 * > 1000, see all msgs, Logger.setDebugLevel(1)
 * send/receive, Logger.printMsg("...", 2);
 * other msgs,  Logger.printMsg("...", 1);
 *
 * For Controller:
 * only print snapshot  Logger.setDebugLevel(2)
 * print other debug    Logger.setDebugLevel(1)
 * snap msg, Logger.printMsg("...", 2);
 * other msgs, Logger.printMsg("...", 1)
 */
public class MyLogger {
    private static int debugLevel;

    public static void setLoggerLevel (int level ){
        debugLevel = level;
    }

    public static void printMsg (String message, int level ){
        if(level >= debugLevel){
            System.out.println(message);
        }
    }

}


