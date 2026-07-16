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
    printf("Compact Form: \n");
    display(compact, t+1, 3);
}

int main() {
    // Transform sparse matrix into compact form <rows, cols, non-zero elements>

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

    // Free allocated memory
    free_memory(matrix, rows);
    free_memory(compact, max_rows);

    return 0;
}