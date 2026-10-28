#include <stdio.h>

#define MAX 20

void input(int matrix[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        printf("[INPUT] ");
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void display(int matrix[MAX][MAX], int rows, int cols, const char *prefix) {
    for (int i = 0; i < rows; i++) {
        printf("%s ", prefix);
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add(int a[MAX][MAX], int b[MAX][MAX],
         int c[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void sub(int a[MAX][MAX], int b[MAX][MAX],
         int c[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
}

void mul(int a[MAX][MAX], int a_rows, int a_cols,
         int b[MAX][MAX], int b_cols, int c[MAX][MAX]) {
    for (int i = 0; i < a_rows; i++) {
        for (int j = 0; j < b_cols; j++) {
            c[i][j] = 0;
            for (int k = 0; k < a_cols; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void tr(int matrix[MAX][MAX], int rows, int cols,
        int tr_matrix[MAX][MAX]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tr_matrix[j][i] = matrix[i][j];
        }
    }
}

int main() {
    // Assignment 1: Matrix operations

    int a_row, a_col, b_row, b_col;
    int a[MAX][MAX], b[MAX][MAX];
    int c[MAX][MAX];
    int a_tr[MAX][MAX], b_tr[MAX][MAX];

    printf("[MESSAGE] Enter Matrix A Size: [Ar Ac]\n");
    scanf("%d %d", &a_row, &a_col);

    printf("[MESSAGE] Enter Matrix B Size: [Br Bc]\n");
    scanf("%d %d", &b_row, &b_col);

    // Validate matrix dimensions
    if (a_row < 1 || a_row > MAX ||
        a_col < 1 || a_col > MAX ||
        b_row < 1 || b_row > MAX ||
        b_col < 1 || b_col > MAX) {
        printf("[DATA] Invalid matrix dimensions. Maximum size is 20x20.\n");
        return 1;
    }

    // Matrix Input
    printf("[MESSAGE] Enter elements of A matrix\n");
    input(a, a_row, a_col);

    printf("[MESSAGE] Enter elements of B matrix\n");
    input(b, b_row, b_col);

    // Matrix Display
    printf("[MESSAGE] Elements of A matrix\n");
    display(a, a_row, a_col, "[MESSAGE]");

    printf("[MESSAGE] Elements of B matrix\n");
    display(b, b_row, b_col, "[MESSAGE]");

    // Menu Driven Program
    int choice;

    printf("[MESSAGE] Functions to perform:\n");
    printf("[MESSAGE] (1) Addition\n");
    printf("[MESSAGE] (2) Subtraction\n");
    printf("[MESSAGE] (3) Multiplication\n");
    printf("[MESSAGE] (4) Transpose\n");
    printf("[MESSAGE] Enter your choice:\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Addition
            if (a_row != b_row || a_col != b_col) {
                printf("[DATA] Matrix Incompatible\n");
            } else {
                add(a, b, c, a_row, a_col);
                printf("[MESSAGE] Addition:\n");
                display(c, a_row, a_col, "[DATA]");
            }
            break;

        case 2:
            // Subtraction
            if (a_row != b_row || a_col != b_col) {
                printf("[DATA] Matrix Incompatible\n");
            } else {
                sub(a, b, c, a_row, a_col);
                printf("[MESSAGE] Subtraction:\n");
                display(c, a_row, a_col, "[DATA]");
            }
            break;

        case 3:
            // Multiplication
            if (a_col != b_row) {
                printf("[DATA] Matrix Incompatible\n");
            } else {
                mul(a, a_row, a_col, b, b_col, c);
                printf("[MESSAGE] Multiplication:\n");
                display(c, a_row, b_col, "[DATA]");
            }
            break;

        case 4:
            // Transpose
            tr(a, a_row, a_col, a_tr);
            tr(b, b_row, b_col, b_tr);

            printf("[MESSAGE] Transpose of A:\n");
            display(a_tr, a_col, a_row, "[DATA]");

            printf("[MESSAGE] Transpose of B:\n");
            display(b_tr, b_col, b_row, "[DATA]");
            break;

        default:
            printf("[DATA] Invalid choice\n");
    }

    printf("[MESSAGE] End\n");

    return 0;
}