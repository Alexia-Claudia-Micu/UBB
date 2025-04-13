package Template;

public abstract class BeverageMakerTemplate {
    // Template method (final so subclasses can't override it)
    public final void makeBeverage() {
        boilWater();
        brew();
        pourIntoCup();
        addCondiments();
    }
    private void boilWater() {
        System.out.println("Boiling water...");
    }
    private void pourIntoCup() {
        System.out.println("Pouring into cup...");
    }
    // Steps to be implemented by subclasses
    protected abstract void brew();
    protected abstract void addCondiments();
}