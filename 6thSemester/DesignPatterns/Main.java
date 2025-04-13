import Adapter.Outlet;
import Adapter.PrinterAdapter;
import Adapter.USBmicro;
import Algorithms.Alg1_0;
import Algorithms.Ieratostene;
import Algorithms.Kadane;
import Algorithms.SlidingWindow;
import Builder.Person;
import Builder.PersonBuilder;
import Builder.PublicPerson;
import Command.Command;
import Command.Remote;
import Command.Light;
import Command.TurnOnCommand;
import Command.TurnOffCommand;
import Decorator.*;
import Factory.MargeritaPizzaFactory;
import Factory.PepperoniPizzaFactory;
import Factory.Pizza;
import Factory.PizzaFactory;
import Observer.PhoneDisplay;
import Observer.TVDisplay;
import Observer.WeatherChannel;
import Strategy.CreditCart;
import Strategy.DebitCard;
import Strategy.PaymentProcessor;
import Prototype.Square;
import Singleton.Singleton;
import Template.BeverageMakerTemplate;
import Template.CoffeeMaker;
import Template.TeaMaker;

import java.util.ArrayList;
import java.util.List;

public class Main {
    private static void singletonPattern(){
        // because getInstance is a static class, we can call it using class name
        Singleton singleton = Singleton.getInstance();
        singleton.doThings();
    }

    private static void PizzaStore(){
        PizzaFactory pizzaFactory;
        Pizza pepperoniPizza, margeritaPizza;

        pizzaFactory = new MargeritaPizzaFactory();
        margeritaPizza = pizzaFactory.createPizza();
        margeritaPizza.bake();

        pizzaFactory = new PepperoniPizzaFactory();
        pepperoniPizza = pizzaFactory.createPizza();
        pepperoniPizza.prepare();
    }

    private static void Adapt(){
        USBmicro usBmicro = new USBmicro();
        Outlet usbMicroToUniversal = new PrinterAdapter(usBmicro);
        usbMicroToUniversal.charge();
    }

    private static void Observe(){
        WeatherChannel weatherChannel = new WeatherChannel();
        PhoneDisplay phoneDisplay = new PhoneDisplay();
        TVDisplay tvDisplay = new TVDisplay();

        weatherChannel.addObserver(phoneDisplay);
        weatherChannel.addObserver(tvDisplay);

        weatherChannel.setWeather(100);

    }

    private static void shapePrototype(){
        Square square = new Square(10);
        Square newSquare = square.clone();

        square.draw();
        newSquare.draw();
    }

    private static void Commander(){
        Remote remote = new Remote();
        Light light = new Light();
        Command turnOn = new TurnOnCommand(light);
        Command turnOff = new TurnOffCommand(light);

        remote.PressButton(turnOff);
        remote.PressButton(turnOn);
    }

    private static void ProcessPayments(){
        PaymentProcessor paymentProcessor = new PaymentProcessor();

        paymentProcessor.ProcessPayment(new CreditCart());
        paymentProcessor.ProcessPayment(new DebitCard());
    }

    private static void StaticBuilder(){
        Person person = new Person.Builder().age(10).address("here").name("person").build();
        System.out.println(person);
    }

    private static void PublicBuilder(){
        PublicPerson person = new PersonBuilder().name("HAHAH").address("There").age(30).build();
        System.out.println(person);
    }

    private static void Decorator(){
        Coffee coffee = new NormalCoffee();
        CoffeeDecorator coffeeDecorator = new CoffeeDecorator(coffee);
        MilkCoffee milkCoffee = new MilkCoffee(coffeeDecorator);
        SugarCoffee sugarAndMilkCoffee = new SugarCoffee(milkCoffee);
        SugarCoffee sugarCoffee = new SugarCoffee(coffeeDecorator);
        System.out.println(coffee.description() + coffee.price());
        System.out.println(coffeeDecorator.description()+coffeeDecorator.price());
        System.out.println(sugarCoffee.description()+sugarCoffee.price());
        System.out.println(sugarAndMilkCoffee.description()+sugarAndMilkCoffee.price());
        System.out.println(milkCoffee.description()+milkCoffee.price());
    }

    private static void Algorithms(){
        List<Integer> list = new ArrayList<>();
        list.add(1);
        list.add(0);
        list.add(0);
        list.add(0);
        list.add(1);
        list.add(1);
        list.add(0);
        list.add(0);
        list.add(0);
        list.add(1);

        Alg1_0 alg = new Alg1_0(list);
        System.out.println(alg.solve_1(1,3));
        System.out.println(alg.solve_1(1,5));
        System.out.println(alg.solve_2(1,3));
        System.out.println(alg.solve_2(1,5));
    }

    private static void IeratostenePrimes(){
        Ieratostene list = new Ieratostene(30000);
        for(int i = 0; i <= 30000; i++){
            System.out.println(i + " = " + list.idPrime(i));
        }
    }

    private static void SolveKadane(){
        int[] arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        Kadane list = new Kadane(arr);
        System.out.println(list.LargestSum());
    }

    private static void SlidingW(){
        int[] arr = {1, 2, 1, 0, 1, 1, 0};
        SlidingWindow slidingWindow = new SlidingWindow(arr);
        System.out.println(slidingWindow.solve(4));
    }

    public static void main(String[] args) {
        BeverageMakerTemplate tea = new TeaMaker();
        tea.makeBeverage();
        System.out.println();

        BeverageMakerTemplate coffee = new CoffeeMaker();
        coffee.makeBeverage();
    }
}
