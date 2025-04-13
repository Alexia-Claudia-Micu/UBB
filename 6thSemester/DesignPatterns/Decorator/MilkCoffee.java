package Decorator;

public class MilkCoffee extends CoffeeDecorator{
    public MilkCoffee(Coffee coffee){
        super(coffee);
    }

    @Override
    public String description(){
        return coffeeDecorator.description() + ", milk";
    }

    @Override
    public float price(){
        return coffeeDecorator.price() + 1.0f;
    }
}
