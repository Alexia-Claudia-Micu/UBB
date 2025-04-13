package Decorator;

public class CoffeeDecorator implements Coffee{
    Coffee coffeeDecorator;

    public CoffeeDecorator(Coffee coffee){this.coffeeDecorator = coffee;}

    @Override
    public String description(){
        return coffeeDecorator.description();
    }

    @Override
    public float price(){
        return coffeeDecorator.price();
    }

}
