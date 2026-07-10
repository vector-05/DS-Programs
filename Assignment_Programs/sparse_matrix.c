#include <stdio.h>

void input(int matrix[100][100], int rows, int cols) { // Matrix Input Func
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("Enter element [%d][%d]: ", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}
}

void display(int matrix[100][100], int rows, int cols) { // Matrix Display Func
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void compaction(int matrix[100][100], int rows, int cols, int compact[100][3]) { // Sparse Matrix Compaction Func

    // non-zero elements (t)
    int t = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0){
                compact[t+1][0] = i;
                compact[t+1][1] = j;
                compact[t+1][2] = matrix[i][j];
                t++;
            }
        }
    }

    // matrix info
    compact[0][0] = rows;
    compact[0][1] = cols;
    compact[0][2] = t;

    // compact form print
    printf("Compact Matrix: \n");
    for (int i = 0; i <= t; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", compact[i][j]);
		}
		printf("\n");
	}
}

int main() {

    // Assignment 2
    // Transform sparse matrix into compact form <rows, cols, non-zero elements>

    // Matrix input & display
    int rows, cols;

    printf("Enter the rows of Matrix: ");
    scanf("%d", &rows);
    printf("Enter the cols of Matrix: ");
    scanf("%d", &cols);

    int matrix[rows][cols];

    printf("Enter elements of Sparse Matrix: \n");
    input(matrix, rows, cols);

    printf("Entered Sparse Matrix: \n");
    display(matrix, rows, cols);

    // compact form
    int compact[100][3];
    compaction(matrix, rows, cols, compact);

    return 0;
}