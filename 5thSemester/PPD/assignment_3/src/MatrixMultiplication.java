public class MatrixMultiplication {

    private final int[][] matrixA;
    private final int[][] matrixB;
    private final int[][] result;
    private final int rows;
    private final int cols;

    public MatrixMultiplication(int[][] matrixA, int[][] matrixB) {
        this.matrixA = matrixA;
        this.matrixB = matrixB;
        this.rows = matrixA.length;
        this.cols = matrixB[0].length;
        this.result = new int[rows][cols];
    }

    // Computes a single element of the resulting matrix
    private int computeElement(int row, int col) {
        int sum = 0;
        for (int k = 0; k < matrixB.length; k++) {
            sum += matrixA[row][k] * matrixB[k][col];
        }
        return sum;
    }

    // Approach 1: Split work by rows
    public void rowWiseTask(int startRow, int endRow) {
        for (int i = startRow; i < endRow; i++) {
            for (int j = 0; j < cols; j++) {
                result[i][j] = computeElement(i, j);
                //System.out.println("calculated element a[" + i + ", " + j + "]");
            }
        }
    }

    // Approach 2: Split work by columns
    public void columnWiseTask(int startCol, int endCol) {
        for (int j = startCol; j < endCol; j++) {
            for (int i = 0; i < rows; i++) {
                result[i][j] = computeElement(i, j);
                //System.out.println("calculated element a[" + i + ", " + j + "]");
            }
        }
    }

    // Approach 3: Every k-th element across rows, based on task ID
    public void kThElementTask(int taskId, int totalTasks) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // Only calculate elements where (i * cols + j) % totalTasks == taskId
                if ((i * cols + j) % totalTasks == taskId) {
                    result[i][j] = computeElement(i, j);
                    //System.out.println("calculated element a[" + i + ", " + j + "]");

                }
            }
        }
    }

    public void printResult() {
        for (int[] row : result) {
            for (int elem : row) {
                System.out.print(elem + " ");
            }
            System.out.println();
        }
    }
}
