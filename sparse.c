#include <stdio.h>
#define MAX 400

typedef struct {
    int row;
    int col;
    int value;
} Term;

void readSparse(Term a[]) {
    int matrix[20][20], rows, cols, i, j, count = 0;
    printf("Enter rows and columns (maximum 20 each): ");
    scanf("%d%d", &rows, &cols);
    if (rows < 1 || cols < 1 || rows > 20 || cols > 20) {
        printf("Invalid dimensions.\n");
        a[0].row = a[0].col = a[0].value = 0;
        return;
    }
    printf("Enter matrix elements:\n");
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            scanf("%d", &matrix[i][j]);
    a[0].row = rows;
    a[0].col = cols;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            if (matrix[i][j] != 0) {
                count++;
                a[count].row = i;
                a[count].col = j;
                a[count].value = matrix[i][j];
            }
    a[0].value = count;
}

void displaySparse(Term a[]) {
    int i;
    printf("Row Col Value\n");
    for (i = 0; i <= a[0].value; i++)
        printf("%3d %3d %5d\n", a[i].row, a[i].col, a[i].value);
}

void simpleTranspose(Term a[], Term b[]) {
    int col, p, q = 1;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;
    for (col = 0; col < a[0].col; col++)
        for (p = 1; p <= a[0].value; p++)
            if (a[p].col == col) {
                b[q].row = a[p].col;
                b[q].col = a[p].row;
                b[q].value = a[p].value;
                q++;
            }
}

void fastTranspose(Term a[], Term b[]) {
    int count[20] = {0}, position[20] = {0};
    int i, col, pos;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;
    if (a[0].value == 0) return;
    for (i = 1; i <= a[0].value; i++)
        count[a[i].col]++;
    position[0] = 1;
    for (col = 1; col < a[0].col; col++)
        position[col] = position[col - 1] + count[col - 1];
    for (i = 1; i <= a[0].value; i++) {
        col = a[i].col;
        pos = position[col]++;
        b[pos].row = a[i].col;
        b[pos].col = a[i].row;
        b[pos].value = a[i].value;
    }
}

int main(void) {
    Term a[MAX], b[MAX];
    int choice, loaded = 0;
    do {
        printf("\n1. Create sparse matrix\n2. Display triplet form\n3. Simple transpose\n4. Fast transpose\n0. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                readSparse(a);
                loaded = a[0].row > 0 && a[0].col > 0;
                break;
            case 2:
                if (loaded) displaySparse(a);
                else printf("Create the matrix first.\n");
                break;
            case 3:
                if (!loaded) printf("Create the matrix first.\n");
                else {
                    simpleTranspose(a, b);
                    displaySparse(b);
                }
                break;
            case 4:
                if (!loaded) printf("Create the matrix first.\n");
                else {
                    fastTranspose(a, b);
                    displaySparse(b);
                }
                break;
            case 0:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}
