package Prototype;

public class Square implements Shape{
    private int length;
    public Square(int len){ this.length = len;}

    @Override
    public Square clone(){
        return new Square(this.length);
    }

    public void draw(){
        System.out.println("Drawing a square with "+ length+" length.");
    }
}
