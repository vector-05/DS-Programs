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

void add(int a[100][100], int b[100][100], int c[100][100], int c_rows, int c_cols) { // Matrix Addition Func
		for (int i = 0; i < c_rows; i++) {
			for (int j = 0; j < c_cols; j++) {
				c[i][j] = a[i][j] + b[i][j];
			}
		}	
}

void sub(int a[100][100], int b[100][100], int c[100][100], int c_rows, int c_cols) { // Matrix Subtraction Func
		for (int i = 0; i < c_rows; i++) {
			for (int j = 0; j < c_cols; j++) {
				c[i][j] = a[i][j] - b[i][j];
			}
		}
}

void mul(int a[100][100], int a_rows, int b[100][100], int b_cols, int c[100][100]) { // Matrix Multiplication Func
	for (int i = 0; i < a_rows; i++) {
		for (int j = 0; j < b_cols; j++) {
			c[i][j] = 0;
            for (int k = 0; k < a_rows; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
		}
	}
}

void tr(int matrix[100][100], int rows, int cols, int tr_matrix[100][100]) { // Matrix Transpose Func
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
	
	int a[a_row][a_col], b[b_row][b_col]; // Matrix Declaration
	
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
				printf("--! Matrix Incompatible !--");
			} else {
				int c[100][100], c_rows = a_row, c_cols = a_col;
				add(a, b, c, c_rows, c_cols);
				display(c, c_rows, c_cols);
			}	
		break;

		case 2: // Subtraction
			if ( !(a_row == b_row) || !(a_col == b_col) ) {
				printf("--! Matrix Incompatible !--\n");
			} else {
				int c[100][100], c_rows = a_row, c_cols = a_col;
				sub(a, b, c, c_rows, c_cols);
				display(c, c_rows, c_cols);
			}
		break;

		case 3: // Multiplication
			if (!(a_row == b_col)) {
				printf("--! Matrix Incompatible !--\n");
			}else {
				int c[100][100], c_row = a_row, c_col = b_col;
				mul(a, a_row, b, b_col, c);
				display(c, c_row, c_col);
			}
		break;

		case 4: // Transpose
			int a_tr[100][100], b_tr[100][100];
			printf("Transpose of A:\n");
			tr(a, a_row, a_col, a_tr);
			display(a_tr, a_col, a_row);
			printf("transpose of B:\n");
			tr(b, b_row, b_col, b_tr);
			display(b_tr, b_col, b_row);
		break;
	}
	
	return 0;
}