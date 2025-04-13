package Template;

public class TeaMaker extends BeverageMakerTemplate {
    @Override
    protected void brew() {
        System.out.println("Steeping the tea...");
    }
    @Override
    protected void addCondiments() {
        System.out.println("Adding lemon...");
    }
}