#include <stdio.h>

int input(char name, int matrix[100][100], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Enter element [%d][%d] of Matrix %c\n", i, j, name); scanf("%d", &matrix[i][j]);
        }
    }
}

void display() {

}

void add() {

}

void sub() {

}

void mul() {

}

void tr() {

}


int main() {

    // Assignment 1
    // Program to Input, Display, Add, Subtract, Multiply and Transpose
    // Number of matrices = 2

    int a_row, a_col, b_row, b_col;

    printf("Enter rows in Matrix A"); scanf("%d\n", &a_row);
    printf("Enter cols in Matrix A"); scanf("%d\n", &a_col);
    printf("Enter rows in Matrix B"); scanf("%d\n", &b_row);
    printf("Enter cols in Matrix B"); scanf("%d\n", &b_col);

    int a[a_row][a_col], b[b_row][b_col];

    input('A', a, a_row, a_col);
    input('B', b, b_row, b_col);

    return 0;
}