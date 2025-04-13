package Observer;

public class TVDisplay implements Observer {
    public TVDisplay(){}

    @Override
    public void update(){
        System.out.println("TV: Weather has changed.");
    }
}
