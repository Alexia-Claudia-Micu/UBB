package Observer;

import java.util.ArrayList;
import java.util.List;

public class WeatherChannel implements Subjects{
    private List<Observer> observers;

    public WeatherChannel(){
        observers = new ArrayList<Observer>();
    }

    @Override
    public void addObserver(Observer observer){
        System.out.println("Added observer.");
        observers.add(observer);
    }

    @Override
    public void removeObserver(Observer observer){
        System.out.println("Removed observer.");
        observers.remove(observer);
    }

    @Override
    public void notifyObservers(){
        for(Observer observer: observers){
            observer.update();
        }
    }

    public void setWeather(int degrees){
        System.out.println("Weather has changed to " + degrees + " degrees.");
        notifyObservers();
    }

}
