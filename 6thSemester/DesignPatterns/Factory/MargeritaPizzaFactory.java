package Factory;

public class MargeritaPizzaFactory implements PizzaFactory{
    public MargeritaPizzaFactory(){}

    @Override
    public Pizza createPizza(){
        System.out.println("Creating a Margerita Pizza.");
        return new MargeritaPizza();
    }
}
