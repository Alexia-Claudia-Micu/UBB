import Algorithms.Parallel;
import Algorithms.ParallelKaratsuba;
import Algorithms.Sequential;
import Algorithms.SequentialKaratsuba;
import Domain.Algorithm;
import Domain.Method;
import Domain.Polynomial;

import java.util.concurrent.ExecutionException;

public class Main {

    private static final Method METHOD = Method.PARALLEL;

    private static final Algorithm ALGORITHM = Algorithm.CLASSIC;
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        Polynomial p1 = new Polynomial(20000);
        System.out.println("Polynomial p1 = " + p1);

        Polynomial p2 = new Polynomial(20000);
        System.out.println("Polynomial p2 = " + p2);

        long startTime = System.nanoTime();

        run(p1, p2);

        long stopTime = System.nanoTime();
        double totalTime = ((double) stopTime - (double) startTime) / 1_000_000_000.0;

        System.out.println("Elapsed running time: " + totalTime + " s");
    }

    private static void run(Polynomial polynomial1, Polynomial polynomial2) throws InterruptedException, ExecutionException {
        Polynomial result = null;
        if(METHOD.equals(Method.SEQUENTIAL)){
            if(ALGORITHM.equals(Algorithm.CLASSIC)){
                result = Sequential.multiply(polynomial1, polynomial2);
            }
            else if(ALGORITHM.equals(Algorithm.KARATSUBA)){
                result = SequentialKaratsuba.multiply(polynomial1, polynomial2);
            }
        } else if (METHOD.equals(Method.PARALLEL)){
            if(ALGORITHM.equals(Algorithm.CLASSIC)){
                result = Parallel.multiply(polynomial1, polynomial2);
            }
            else if(ALGORITHM.equals(Algorithm.KARATSUBA)){
                result = ParallelKaratsuba.multiply(polynomial1, polynomial2, 1);
            }
        }

        System.out.println("p1 * p2 = " + result.toString());
    }
}