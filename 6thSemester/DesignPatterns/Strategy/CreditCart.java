package Strategy;

public class CreditCart implements PaymentMethod{
    public CreditCart(){}

    @Override
    public void Pay(){
        System.out.println("Pay with Credit Card.");
    }
}
