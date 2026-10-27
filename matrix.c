#include <stdio.h>
#define MAX 20

void readMatrix(int a[MAX][MAX], int *r, int *c) {
    int i, j;
    printf("Enter rows and columns: ");
    scanf("%d%d", r, c);
    if (*r < 1 || *c < 1 || *r > MAX || *c > MAX) {
        printf("Invalid dimensions.\n");
        *r = *c = 0;
        return;
    }
    printf("Enter matrix elements:\n");
    for (i = 0; i < *r; i++)
        for (j = 0; j < *c; j++)
            scanf("%d", &a[i][j]);
}

void displayMatrix(int a[MAX][MAX], int r, int c) {
    int i, j;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

int main(void) {
    int a[MAX][MAX], b[MAX][MAX], result[MAX][MAX];
    int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    int i, j, k, choice, loaded = 0;
    do {
        printf("\n1. Read matrices\n2. Addition\n3. Subtraction\n4. Multiplication\n5. Transpose\n0. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                readMatrix(a, &r1, &c1);
                if (r1 && c1) {
                    readMatrix(b, &r2, &c2);
                    loaded = (r2 && c2);
                } else loaded = 0;
                break;
            case 2:
            case 3:
                if (!loaded) {
                    printf("Read both matrices first.\n");
                    break;
                }
                if (r1 != r2 || c1 != c2) {
                    printf("Matrices must have the same dimensions.\n");
                    break;
                }
                for (i = 0; i < r1; i++)
                    for (j = 0; j < c1; j++)
                        result[i][j] = choice == 2 ? a[i][j] + b[i][j] : a[i][j] - b[i][j];
                displayMatrix(result, r1, c1);
                break;
            case 4:
                if (!loaded) {
                    printf("Read both matrices first.\n");
                    break;
                }
                if (c1 != r2) {
                    printf("Columns of first matrix must equal rows of second matrix.\n");
                    break;
                }
                for (i = 0; i < r1; i++)
                    for (j = 0; j < c2; j++) {
                        result[i][j] = 0;
                        for (k = 0; k < c1; k++)
                            result[i][j] += a[i][k] * b[k][j];
                    }
                displayMatrix(result, r1, c2);
                break;
            case 5: {
                int which, r, c;
                printf("Transpose which matrix (1 or 2)? ");
                scanf("%d", &which);
                if (!loaded || (which != 1 && which != 2)) {
                    printf("Read matrices first and choose 1 or 2.\n");
                    break;
                }
                r = which == 1 ? r1 : r2;
                c = which == 1 ? c1 : c2;
                for (i = 0; i < c; i++) {
                    for (j = 0; j < r; j++)
                        printf("%d ", which == 1 ? a[j][i] : b[j][i]);
                    printf("\n");
                }
                break;
            }
            case 0:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}
