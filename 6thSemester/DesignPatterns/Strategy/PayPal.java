package Strategy;

public class PayPal implements PaymentMethod{
    public PayPal(){}

    @Override
    public void Pay(){
        System.out.println("Paying with PayPal.");
    }
}
