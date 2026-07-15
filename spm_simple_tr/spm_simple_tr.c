#include <stdio.h>
#include <stdlib.h>

int **allocate_memory(int rows, int cols) {
	int **matrix = (int **)malloc(rows * sizeof(int *));
	for (int i = 0; i < rows; i++) {
		matrix[i] = (int *)malloc(cols * sizeof(int ));
	}
	return matrix;
}

void free_memory(int **matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void input(int **matrix, int rows, int cols) { // Matrix Input Func
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
}

void display(int **matrix, int rows, int cols) { // Matrix Display
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void compaction(int **matrix, int rows, int cols, int **compact) { // Sparse Matrix Compaction Func

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
    printf("Compact Form:\n");
    display(compact, t+1, 3);
}

void simple_transpose(int **compact, int **transpose) { // simple transpose of sparse matrix

    // matrix info
    int non_zero_elements = compact[0][2];
    int rows = compact[0][0];
    int cols = compact[0][1];

    transpose[0][0] = cols;
    transpose[0][1] = rows;
    transpose[0][2] = non_zero_elements;

    int k = 1; // transpose array new row pointer

    for (int i = 0; i < cols; i++) {
        for (int j = 1; j <= non_zero_elements; j++) {
            if ( i == compact[j][1]) {
                transpose[k][0] = compact[j][1];
                transpose[k][1] = compact[j][0];
                transpose[k][2] = compact[j][2];
                k++;
            }
        }
    }

    // display transpose matrix
    printf("Simple Transpose: \n");
    display(transpose, non_zero_elements + 1, 3);
}

int main() {
    // Transpose of Sparse Matrix using Fast Transpose

    // Matrix input & display
    int rows, cols;

    printf("Enter the size of Matrix: ");
    scanf("%d %d", &rows, &cols);

    int **matrix = allocate_memory(rows, cols);

    printf("Enter elements of Sparse Matrix: \n");
    input(matrix, rows, cols);

    printf("Entered Sparse Matrix: \n");
    display(matrix, rows, cols);

    // compact form
    int max_rows = rows * cols + 1;
    int **compact = allocate_memory(max_rows, 3);
    compaction(matrix, rows, cols, compact);

    // simple transpose of compact form
    int **transpose = allocate_memory(max_rows, 3);
    simple_transpose(compact, transpose);

    // Free allocated memory
    free_memory(matrix, rows);
    free_memory(compact, max_rows);
    free_memory(transpose, max_rows);

    return 0;
}