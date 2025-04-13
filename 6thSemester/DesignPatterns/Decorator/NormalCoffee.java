package Decorator;

public class NormalCoffee implements Coffee{
    public NormalCoffee(){}

    @Override
    public String description(){
        return "Normal coffee";
    }

    @Override
    public float price(){
        return 10;
    }
}
