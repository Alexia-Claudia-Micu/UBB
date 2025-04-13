package Decorator;

public class SugarCoffee extends CoffeeDecorator{
    public SugarCoffee(Coffee coffee){
        super(coffee);
    }

    @Override
    public String description(){
        return coffeeDecorator.description() + ", sugar";
    }

    @Override
    public float price(){
        return coffeeDecorator.price() + 0.5f;
    }
}
