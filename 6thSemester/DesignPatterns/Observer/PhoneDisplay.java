package Observer;

public class PhoneDisplay implements Observer{
    public PhoneDisplay(){}

    @Override
    public void update(){
        System.out.println("Phone: Weather has changed.");
    }

}
