import java.util.Scanner;

class Imatrix {
	public static void main(String args[]) {
        System.out.println();
        System.out.println("*************************");
        System.out.println("Inverse Matrix Calculator");
        System.out.println();
		Scanner in = new Scanner(System.in);
		int n; // matrix size
		System.out.println("What size of the matrix?");
		n = in.nextInt();
		double[][] m = new double[n][n];
        if (n <= 1) {
            System.out.println("Cannot be a matrix");
        }
		System.out.println("Enter the numbers for matrix");
		Scanner input = new Scanner(System.in);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				m[i][j] = input.nextDouble();
			}
		}
		double det = determinant(m, n);
		double[][] cofactorMatrix = cofactor(m, n, n);

      	     	
        System.out.println("The inverse matrix is: ");
        printMatrix(transpose(cofactorMatrix, n), n, det); 
	}

    public static double[][] transpose(double[][] matrix, int size) {
        double transposed[][] = new double[size][size];
        for (int i = 0 ; i < size ; i++ ) {
            for (int j = 0 ; j < size ; j++ ) {              
                transposed[j][i] = matrix[i][j];
            }
        } 
        return transposed;
    }

    public static void printMatrix(double[][] matrix, int size, double divider) {
        for (int i = 0 ; i < size ; i++ ) {
            for (int j = 0 ; j < size ; j++ ) {
               System.out.print(matrix[i][j]/divider +  "   ");
           }
           System.out.println();
           System.out.println();
        }
    }

	public static double[][] cofactor(double[][] matrix, int rows, int cols) {
	    double[][] result = new double[rows][cols];

	    for (int i = 0; i < rows; i++) {
	        for (int j = 0; j < cols; j++) {
	            result[i][j] = (int) (Math.pow(-1, i + j) * determinant(
	                    removeRowCol(matrix, rows, cols, i, j), rows - 1));
	        }
	    }
	    return result;
	}

	public static double[][] removeRowCol(double[][] matrix, int rows, int cols,
	        int row, int col) {
	    double[][] result = new double[rows - 1][cols - 1];
	    int k = 0, l = 0;
	    for (int i = 0; i < rows; i++) {
	        if (i == row)
	            continue;
	        for (int j = 0; j < cols; j++) {
	            if (j == col)
	                continue;
	            result[l][k] = matrix[i][j];
	            k = (k + 1) % (rows - 1);
	            if (k == 0)
	                l++;
	        }
	    }
	    return result;
	}
    public static double determinant(double A[][], int n) {
        double det=0;
        if(n == 1)
        {
            det = A[0][0];
        }
        else if (n == 2)
        {
            det = A[0][0]*A[1][1] - A[1][0]*A[0][1];
        }
        else
        {
            det=0;
            for(int j1=0;j1<n;j1++)
            {
                double[][] m = new double[n-1][];
                for(int k=0;k<(n-1);k++)
                {
                    m[k] = new double[n-1];
                }
                for(int i=1;i<n;i++)
                {
                    int j2=0;
                    for(int j=0;j<n;j++)
                    {
                        if(j == j1)
                            continue;
                        m[i-1][j2] = A[i][j];
                        j2++;
                    }
                }
                det += Math.pow(-1.0,1.0+j1+1.0)* A[0][j1] * determinant(m,n-1);
            }
        }
        return det;
    }
}

//http://stackoverflow.com/questions/21153823/determining-cofactor-matrix-in-java provided help for cofactoring method
//http://www.sanfoundry.com/java-program-compute-determinant-matrix/ for determinant