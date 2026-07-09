#include <stdio.h>

void input(int matrix[100][100], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("Enter element [%d][%d]: ", i, j); scanf("%d\n", &matrix[i][j]);
		}
	}
}

void display(int matrix[100][100], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void add(int a[100][100], int b[100][100], c[100][100], int c_rows, int c_cols) {
		
		for (int i = 0; i < c_rows; i++) {
			for (int j = 0; j < c_cols; j++) {
				c[i][j] = a[i][j] + b[i][j];
				}
			}	
	}
}

int sub() {
	return 0;
}

int mul() {
	return 0;
}

int tr() {
	return 0;
}

int main() {
	
	// Assignment 1
	// C program to compute following on matrix: addition; subtraction; multiplication; transpose
	
	int a_row, a_col, b_row, b_col;
	
	printf("Enter rows of A Matrix: "); scanf("%d\n", &a_row);
	printf("Enter cols of A Matrix: "); scanf("%d\n", &a_col);
	printf("Enter rows of B Matrix: "); scanf("%d\n", &b_row);
	printf("Enter cols of B Matrix: "); scanf("%d\n", &b_col);
	
	int a[a_row][a_col], b[b_row][b_col];
	
	
	printf("Enter elements of A matrix\n"); input(a, a_row, a_col);
	printf("Enter elements of B matrix\n"); input(b, b_row, b_col);
	
	printf("Elements of A matrix\n"); display(a, a_row, a_col);
	printf("Elements of B matrix\n"); display(b, b_row, b_col);
	
	int choice;
	
	printf("Functions to perform: \n (1) Addition \n (2) Subtraction \n (3) Multiplication \n (4) Transpose \n Enter the function to perform: "); scanf("%d", &choice);
	switch (choice) {
		case 1:
			if ( !(a_rows == b_rows) || !(a_cols == b_cols) ) {
				printf("--! Matrix Incompatible !--");
			} else {
				int c[100][100], c_rows = a_row, c_cols = a_col;
				add(a, b, c, c_rows, c_cols);
			}
			
		break;
		case 2: break;
		case 3: break;
		case 4: break;
		default: break;
	}
	
	return 0;
}