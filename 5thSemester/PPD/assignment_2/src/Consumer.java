import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Consumer {
    public static void main(String[] args) {
        int scalarProduct = 0;

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String line;
            while ((line = reader.readLine()) != null && !line.trim().isEmpty()) {                int partialProduct = Integer.parseInt(line);
                scalarProduct += partialProduct;
            }
        } catch (NumberFormatException e) {
            System.err.println("Invalid number format: " + e.getMessage());
        } catch (Exception e) {
            e.printStackTrace();
        }

        System.out.println("Scalar product: " + scalarProduct);
    }
}
