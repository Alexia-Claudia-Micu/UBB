package Strategy;

public class DebitCard implements PaymentMethod{
    public DebitCard(){};

    @Override
    public void Pay(){
        System.out.println("Paying with Debit Card.");
    }
}
