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
    display(compact, t+1, 3);
}

int addition(int **a, int **b) {    // Addition of sparse matrix (modified with flag operation)
    if ( (a[0][0] == b[0][0]) && (a[0][1] == b[0][1]) ) {
        // intialize conditions
        int t1 = a[0][2];
        int t2 = b[0][2];
        
        // empty check
        if ( (t1 == 0) && (t2 == 0) ) {
            return -1;
        } else {
            // pointer variables
            int i = j = k = 1;
            
            // result matrix
            int **c = allocate_memory(a[0][0], a[0][1]);
            c[0][0] = a[0][0];
            c[0][1] = a[0][1];

            // code loop
            while ( (i <= t1) && (j <= t2) ) {
                int row_compare = (a[i][0] > b[j][0]) - (a[i][0] < b[j][0]); // row condition
                switch (row_compare) {
                    case 0: 
                        int col_compare = (a[i][1] > b[j][1]) - (a[i][1] < b[j][1]);    // col condition
                        switch (col_compare) {
                            case 0: 
                                if (!((a[i][2] + b[j][2]) == 0)) {
                                    c[k][0] = a[i][0];
                                    c[k][1] = a[i][1];
                                    c[k][2] = a[i][2] + b[j][2];
                                    k++;
                                }
                                i++;
                                j++;
                                break;
                            case 1: 
                                c[k][0] = b[j][0];
                                c[k][1] = b[j][1];
                                c[k][2] = b[j][2];
                                k++;
                                j++;
                                break;
                            case -1: 
                                c[k][0] = a[i][0];
                                c[k][1] = a[i][1];
                                c[k][2] = a[i][2];
                                k++;
                                i++;
                                break;
                            default: return -1;
                        }
                        break;
                    case 1: 
                        c[k][0] = b[j][0];
                        c[k][1] = b[j][1];
                        c[k][2] = b[j][2];
                        k++;
                        j++;
                        break;
                    case -1:
                        c[k][0] = a[i][0];
                        c[k][1] = a[i][1];
                        c[k][2] = a[i][2];
                        k++;
                        i++;
                        break;
                    default: return -1;
                }
            }

            // complete the rest of the code

            free_memory(c, a[0][0]);
        }

    } else {
        return -1;
    }
}

int main() {
    // Addition of two sparse matrix

    // Matrix Info - User Input	

	int a_row, a_col, b_row, b_col;
	printf("Enter Matrix A Size: [Ar Ac]\n");
	scanf("%d %d", &a_row, &a_col);
	printf("Enter Matrix B Size: [Br Bc]\n");
	scanf("%d %d", &b_row, &b_col);
	
	int **a = allocate_memory(a_row, a_col); // Matrix Declaration
	int **b = allocate_memory(b_row, b_col); // Matrix Declaration

	// Matrix Input
	printf("Enter elements of A matrix\n"); 
	input(a, a_row, a_col);
	printf("Enter elements of B matrix\n"); 
	input(b, b_row, b_col);
	
	// Matrix Display
	printf("Elements of A matrix\n"); 
	display(a, a_row, a_col);
	printf("Elements of B matrix\n"); 
	display(b, b_row, b_col);

    // compact form
    int **a_compact = allocate_memory(a_row * a_col + 1, 3);
    compaction(a, a_row, a_col, a_compact);
    int **b_compact = allocate_memory(b_row * b_col + 1, 3);
    compaction(b, b_row, b_col, b_compact);

    // Addition
    flag = addition(a, b);

    // Free allocated memory
    free_memory(a, a_row);
    free_memory(b, b_row);
    free_memory(a_compact, a_row * a_col + 1);
    free_memory(b_compact, b_row * b_col + 1);

    return 0;
}