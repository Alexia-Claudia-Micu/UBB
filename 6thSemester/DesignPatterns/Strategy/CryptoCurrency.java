package Strategy;

public class CryptoCurrency implements PaymentMethod{
    public CryptoCurrency(){}

    @Override
    public void Pay(){
        System.out.println("Paying with CryptoCurrency.");
    }
}
