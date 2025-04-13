package Factory;

public class MargeritaPizza implements Pizza{
    public MargeritaPizza(){
        System.out.println("Margerita Pizza instantiated.");
    }

    @Override
    public void prepare(){
        System.out.println("Preparing Margerita Pizza.");
    }

    @Override
    public void bake(){
        System.out.println("Baking Margerita Pizza.");
    }

    @Override
    public void cut(){
        System.out.println("Cutting Margerita Pizza into 8 slices.");
    }

    @Override
    public void box(){
        System.out.println("Placing Margerita Pizza in a box.");
    }
}
