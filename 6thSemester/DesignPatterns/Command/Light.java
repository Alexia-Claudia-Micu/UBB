package Command;

import java.util.SortedMap;

public class Light {
    String lightState;
    public Light(){ lightState = "off";}

    public void turnOn(){
        lightState = "on";
        System.out.println("Light has been turned on.");
    }

    public void turnOff(){
        lightState = "off";
        System.out.println("Light has been turned off.");
    }
}
