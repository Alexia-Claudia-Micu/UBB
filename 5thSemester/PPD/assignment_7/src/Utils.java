import java.util.ArrayList;
import java.util.List;

public class Utils {
    public static Polynomial getResult(Object[] polynomials) {
        int size = ((Polynomial) polynomials[0]).getDegree();
        Polynomial result = new Polynomial(size + 1);
        for (Object polynomial: polynomials) {
            result = Polynomial.add(result, (Polynomial) polynomial);
        }
        return result;
    }

    public static Polynomial multiplySequence(Polynomial p1, Polynomial p2, int start, int end) {
        Polynomial result = new Polynomial(p1.getSize() + p2.getSize() - 1);
        for (int i = start; i < end; i++) {
            for (int j = 0; j < p2.getSize(); j++) {
                result.getCoefficients().set(i + j, result.getCoefficients().get(i + j) + p1.getCoefficients().get(i) * p2.getCoefficients().get(j));
            }
        }
        return result;
    }

    public static Polynomial KaratsubaSequential(Polynomial p1, Polynomial p2) {
        int n = Math.max(p1.getSize(), p2.getSize());

        // Base case: if polynomials are of size 1, multiply directly
        if (n == 1) {
            int result = p1.getCoefficients().get(0) * p2.getCoefficients().get(0);
            List<Integer> coefficients = new ArrayList<>();
            coefficients.add(result);
            return new Polynomial(coefficients);
        }

        // Pad polynomials to the same size (power of 2 for simplicity)
        p1 = p1.padToSize(n);
        p2 = p2.padToSize(n);

        int m = n / 2; // Split size

        // Split polynomials into low and high parts
        Polynomial A_low = p1.getLowPart(m);
        Polynomial A_high = p1.getHighPart(m);
        Polynomial B_low = p2.getLowPart(m);
        Polynomial B_high = p2.getHighPart(m);

        // Recursively compute the three products
        Polynomial z0 = KaratsubaSequential(A_low, B_low);
        Polynomial z2 = KaratsubaSequential(A_high, B_high);

        // (A_low + A_high) * (B_low + B_high)
        Polynomial A_sum = Polynomial.add(A_low, A_high);
        Polynomial B_sum = Polynomial.add(B_low, B_high);
        Polynomial z1 = KaratsubaSequential(A_sum, B_sum);

        // Combine results: result = z2 * x^(2m) + (z1 - z2 - z0) * x^m + z0
        Polynomial z1_minus_z2_z0 = Polynomial.subtract(Polynomial.subtract(z1, z2), z0);

        Polynomial result = Polynomial.add(
                Polynomial.add(z0, z1_minus_z2_z0.shift(m)),
                z2.shift(2 * m)
        );

        return result;
    }

}
