import mpi.MPI;

/*
to run:
in C:\Users\alexi\OneDrive\Documents\Facultate\Anul_3\Sem_1\PPD\assignment_7\src
run javac -cp "C:\mpj\lib\mpj.jar" *.java

in C:\mpj
run bin\mpjrun.bat -np 4 -cp "C:\Users\alexi\OneDrive\Documents\Facultate\Anul_3\Sem_1\PPD\assignment_7\src;C:\mpj\lib\mpj.jar" Main
 */

public class Main {
    static final int POLYNOMIAL_SIZE = 10000;
    static final String IMPLEMENTATION = "regular";

    public static void master(Polynomial p1, Polynomial p2, int processes) {
        long startTime = System.nanoTime();

        int length = p1.getSize() / (processes - 1);  // Divide work among processes
        int start;
        int end = 0;

        System.out.println("Distributing work among " + (processes - 1) + " worker processes...\n");

        // Sending data to workers
        for (int i = 1; i < processes; i++) {
            start = end;
            end = start + length;
            if (i == processes - 1) {
                end = p1.getSize();
            }

            System.out.println("Sending data to worker " + i + " (range: " + start + " to " + end + ")");

            // Send the polynomial and index range to each worker
            MPI.COMM_WORLD.Send(new Object[]{p1}, 0, 1, MPI.OBJECT, i, 0);
            MPI.COMM_WORLD.Send(new Object[]{p2}, 0, 1, MPI.OBJECT, i, 0);
            MPI.COMM_WORLD.Send(new int[]{start}, 0, 1, MPI.INT, i, 0);
            MPI.COMM_WORLD.Send(new int[]{end}, 0, 1, MPI.INT, i, 0);
        }

        // Receive results from workers
        Object[] results = new Object[processes - 1];
        for (int i = 1; i < processes; i++) {
            System.out.println("Receiving result from worker " + i);
            MPI.COMM_WORLD.Recv(results, i - 1, 1, MPI.OBJECT, i, 0);
        }

        // Combine results
        Polynomial result = Utils.getResult(results);

        long endTime = System.nanoTime();
        double duration = (endTime - startTime) / 1000000000.0;

        System.out.println("\n" + IMPLEMENTATION + " Polynomial Multiplication Completed:");
        System.out.println("Execution time: " + duration + " seconds");
    }

    public static void regularWorker(int me) {
        Object[] p1 = new Object[2];
        Object[] p2 = new Object[2];
        int[] start = new int[1];
        int[] end = new int[1];

        MPI.COMM_WORLD.Recv(p1, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(p2, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(start, 0, 1, MPI.INT, 0, 0);
        MPI.COMM_WORLD.Recv(end, 0, 1, MPI.INT, 0, 0);

        Polynomial pol1 = (Polynomial) p1[0];
        Polynomial pol2 = (Polynomial) p2[0];

        Polynomial result = Utils.multiplySequence(pol1, pol2, start[0], end[0]);
        MPI.COMM_WORLD.Send(new Object[]{result}, 0, 1, MPI.OBJECT, 0, 0);
    }

    public static void karatsubaWorker(int me) {
        Object[] p1 = new Object[1];
        Object[] p2 = new Object[1];
        int[] start = new int[1];
        int[] end = new int[1];

        // Receive data from the master
        MPI.COMM_WORLD.Recv(p1, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(p2, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(start, 0, 1, MPI.INT, 0, 0);
        MPI.COMM_WORLD.Recv(end, 0, 1, MPI.INT, 0, 0);

        Polynomial pol1 = (Polynomial) p1[0];
        Polynomial pol2 = (Polynomial) p2[0];

        System.out.println("Worker " + me + " started Karatsuba computation");

        // Extract the assigned range and zero out other parts
        for (int i = 0; i < start[0]; i++) {
            pol1.getCoefficients().set(i, 0);
        }
        for (int j = end[0]; j < pol1.getCoefficients().size(); j++) {
            pol1.getCoefficients().set(j, 0);
        }

        // Compute the Karatsuba product for this portion
        Polynomial result = Utils.KaratsubaSequential(pol1, pol2);

        System.out.println("Worker " + me + " finished, sending result to master");

        // Send result back to master
        MPI.COMM_WORLD.Send(new Object[]{result}, 0, 1, MPI.OBJECT, 0, 0);
    }

    public static void main(String[] args) {
        MPI.Init(args);
        int me = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        if (me == 0) {
            System.out.println("Master process: \n");
            Polynomial p1 = new Polynomial(POLYNOMIAL_SIZE);
            p1.generateCoefficients();
            Polynomial p2 = new Polynomial(POLYNOMIAL_SIZE);
            p2.generateCoefficients();

            master(p1, p2, size);
        } else {
            if (IMPLEMENTATION.equalsIgnoreCase("regular")) {
                regularWorker(me);
            }
            else if (IMPLEMENTATION.equalsIgnoreCase("karatsuba")) {
                karatsubaWorker(me);
            }
        }
        MPI.Finalize();
    }
}
