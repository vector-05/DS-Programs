#include <stdio.h>
#include <stdlib.h>

int **allocate_memory(int rows, int cols) {
	int **matrix = (int **)malloc(rows * sizeof(int *));
	for (int i = 0; i < rows; i++) {
		matrix[i] = (int *)malloc(cols * sizeof(int *));
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
		printf("[Data] ")	// automation tag
		for (int j = 0; j < cols; j++) {
			printf("Enter element [%d][%d]: ", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}
}

void display(int **matrix, int rows, int cols) { // Matrix Display Func
	for (int i = 0; i < rows; i++) {
		printf("[Data] ")	// automation tag
		for (int j = 0; j < cols; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void add(int **a, int **b, int **c, int c_rows, int c_cols) { // Matrix Addition Func
		for (int i = 0; i < c_rows; i++) {
			for (int j = 0; j < c_cols; j++) {
				c[i][j] = a[i][j] + b[i][j];
			}
		}	
}

void sub(int **a, int **b, int **c, int c_rows, int c_cols) { // Matrix Subtraction Func
		for (int i = 0; i < c_rows; i++) {
			for (int j = 0; j < c_cols; j++) {
				c[i][j] = a[i][j] - b[i][j];
			}
		}
}

void mul(int **a, int a_rows, int a_cols, int **b, int b_cols, int **c) { // Matrix Multiplication Func
	for (int i = 0; i < a_rows; i++) {
		for (int j = 0; j < b_cols; j++) {
			c[i][j] = 0;
            for (int k = 0; k < a_cols; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
		}
	}
}

void tr(int **matrix, int rows, int cols, int **tr_matrix) { // Matrix Transpose Func
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			tr_matrix[j][i] = matrix[i][j];
		}
	}
}

int main() {
	
	// Assignment 1
	// C program to compute following on matrix: addition; subtraction; multiplication; transpose
	
	int a_row, a_col, b_row, b_col;

	// Matrix Info - User Input	
	printf("Enter rows of A Matrix: ");
	scanf("%d", &a_row);
	printf("Enter cols of A Matrix: ");
	scanf("%d", &a_col);
	printf("Enter rows of B Matrix: ");
	scanf("%d", &b_row);
	printf("Enter cols of B Matrix: ");
	scanf("%d", &b_col);
	
	int **a = allocate_memory(a_row, a_col); // Matrix Declaration
	int **b = allocate_memory(b_row, b_col);

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
	

	// Menu Driven Program
	int choice;
	
	printf("Functions to perform: \n (1) Addition \n (2) Subtraction \n (3) Multiplication \n (4) Transpose \n"); 
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) {
		case 1: // Addition
			if ( !(a_row == b_row) || !(a_col == b_col) ) {
				printf("[MESSAGE] --! Matrix Incompatible !--");
			} else {
				int **c = allocate_memory(a_row, a_col);
				add(a, b, c, a_row, a_col);
				printf("Addition: \n");
				display(c, a_row, a_col);
				free_memory(c, a_row);
			}	
		break;

		case 2: // Subtraction
			if ( !(a_row == b_row) || !(a_col == b_col) ) {
				printf("[MESSAGE] --! Matrix Incompatible !--\n");
			} else {
				int **c = allocate_memory(a_row, a_col);
				sub(a, b, c, a_row, a_col);
				printf("Subtraction: \n");
				display(c, a_row, a_col);
				free_memory(c, a_row);
			}
		break;

		case 3: // Multiplication
			if (!(a_row == b_col)) {
				printf("[MESSAGE] --! Matrix Incompatible !--\n");
			}else {
				int **c = allocate_memory(a_row, a_col);
				mul(a, a_row, a_col, b, b_col, c);
				display(c, a_row, b_col);
				free_memory(c, a_row);
			}
		break;

		case 4: // Transpose
			int **a_tr = allocate_memory(a_col, a_row);
			int **b_tr = allocate_memory(b_col, b_row);

			printf("Transpose of A:\n");
			tr(a, a_row, a_col, a_tr);
			display(a_tr, a_col, a_row);

			printf("transpose of B:\n");
			tr(b, b_row, b_col, b_tr);
			display(b_tr, b_col, b_row);

			free_memory(a_tr, a_row);
			free_memory(b_tr, b_row);
		break;
	}

	printf("--! End !--\n");
	return 0;
}