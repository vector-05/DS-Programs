#include <stdio.h>
#include <stdlib.h>

struct student students[20] {
    int rollno,
    char[10] name,
}

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

int input() {
    return 0;
}

int display() {
    return 0;
}

int linear_search() {
    return 0;
}

/*
Complete the Program
*/

int main() {
    return 0;
}