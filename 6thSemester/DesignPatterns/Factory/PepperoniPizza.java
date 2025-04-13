package Factory;

import javax.sound.midi.Soundbank;

public class PepperoniPizza implements Pizza{
    public PepperoniPizza(){
        System.out.println("Pepperoni Pizza instantiated.");
    }

    @Override
    public void prepare(){
        System.out.println("Preparing Pepperoni Pizza.");
    }

    @Override
    public void bake(){
        System.out.println("Baking Pepperoni Pizza.");
    }

    @Override
    public void cut(){
        System.out.println("Cutting Pepperoni Pizza into 9 slices.");
    }

    @Override
    public void box(){
        System.out.println("Placing Pepperoni Pizza into a box.");
    }
}
