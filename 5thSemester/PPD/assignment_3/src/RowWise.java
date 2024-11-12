public class RowWise {
    public static void main(String[] args) throws InterruptedException {
        int[][] matrixA = {
                {1, 2, 3, 4, 5, 6, 7, 8, 9},
                {0, 1, 0, 0, 0, 0, 0, 5, 0},
                {0, 1, 0, 0, 0, 0, 0, 4, 0},
                {1, 1, 2, 3, 4, 5, 6, 3, 7},
                {0, 1, 0, 0, 0, 0, 0, 2, 0},
                {3, 1, 4, 2, 6, 8, 5, 1, 8},
                {0, 1, 0, 4, 0, 9, 0, 2, 0},
                {0, 1, 0, 6, 0, 6, 0, 3, 0},
                {0, 1, 0, 8, 0, 7, 0, 4, 0}
        };
        int[][] matrixB = {
                {10, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 1, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 1, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 1, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 1, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 1}
        };

        MatrixMultiplication multiplication = new MatrixMultiplication(matrixA, matrixB);

        Thread t1 = new Thread(() -> multiplication.rowWiseTask(0, 2));
        Thread t2 = new Thread(() -> multiplication.rowWiseTask(2, 4));
        Thread t3 = new Thread(() -> multiplication.rowWiseTask(4, 6));
        Thread t4 = new Thread(() -> multiplication.rowWiseTask(6, 9));

        t1.start();
        t2.start();
        t3.start();
        t4.start();

        t1.join();
        t2.join();
        t3.join();
        t4.join();

        System.out.println("Result (Row-wise split):");
        multiplication.printResult();
    }
}
