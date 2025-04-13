package Factory;

public class PepperoniPizzaFactory implements PizzaFactory{
    public PepperoniPizzaFactory(){}

    @Override
    public Pizza createPizza(){
        System.out.println("Creating a Pepperoni Pizza.");
        return new PepperoniPizza();
    }
}
