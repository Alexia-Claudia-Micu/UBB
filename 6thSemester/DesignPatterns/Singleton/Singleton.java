package Singleton;

public class Singleton{
    // has private static instance of itself
    private static Singleton instance;

    // has private constructor such that you can control it to have only one instance
    private Singleton(){
        System.out.println("Singular instance created.");
    }

    // public static getter
    public static Singleton getInstance(){
        if(instance == null){
            instance = new Singleton();
        }
        return instance;
    }

    public void doThings(){
        System.out.println("doing things");
    }
}