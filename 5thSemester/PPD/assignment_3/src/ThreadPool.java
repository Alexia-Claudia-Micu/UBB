import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class ThreadPool {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        int[][] matrixA = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
        };
        int[][] matrixB = {
                {1, 0, 0},
                {0, 1, 0},
                {0, 0, 1}
        };

        MatrixMultiplication multiplication = new MatrixMultiplication(matrixA, matrixB);
        int numTasks = 3;
        ExecutorService executor = Executors.newFixedThreadPool(numTasks);

        Future<?> task1 = executor.submit(() -> multiplication.rowWiseTask(0, 1));
        Future<?> task2 = executor.submit(() -> multiplication.rowWiseTask(1, 2));
        Future<?> task3 = executor.submit(() -> multiplication.rowWiseTask(2, 3));

        task1.get();
        task2.get();
        task3.get();

        System.out.println("Result (Row-wise split with Thread Pool):");
        multiplication.printResult();

        executor.shutdown();
    }
}
