import java.io.PrintWriter;

public class Producer {
    private static final int[] vectorA = {1, 3, 5, 7, 9};
    private static final int[] vectorB = {2, 4, 6, 8, 10};

    public static void main(String[] args) {
        try (PrintWriter writer = new PrintWriter(System.out)) {
            for (int i = 0; i < vectorA.length; i++) {
                int partialProduct = vectorA[i] * vectorB[i];
                writer.println(partialProduct);
                writer.flush();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
