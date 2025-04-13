package Strategy;

public class PaymentProcessor {
    public PaymentProcessor(){}

    public void ProcessPayment(PaymentMethod paymentMethod){
        paymentMethod.Pay();
    }
}
