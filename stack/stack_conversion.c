#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

// Standard Stack Implementation

int IsFull(int S[MAX], int *top){
    if (*top == MAX - 1) {
        return 1;
    } else {
        return 0;
    }
}

int IsEmpty(int S[MAX], int *top) {
    if (*top == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

int push(int S[MAX], int *top, int x) {
    if (IsFull(S, top)) {
        printf("Stack Overflow!");
    } else {
        *top = *top + 1;
        S[*top] = x;
    }
    return 0;
}

int pop(int S[MAX], int *top) {
    if (IsEmpty(S, top)) {
        printf("Stack Underflow!");
        return 0;
    } else {
        int x = S[*top];
        *top = *top - 1;
        return x;
    }
}

int display(int S[MAX], int *top) {
    for (int i = 0; i <= *top; i++) {
        printf("%d ", S[i]);
    }
    printf("\n");
    return 0;
}

int main() {

    printf("Welcome to stack Operations...\n");
    printf("Initiating Empty Stack...\n");
    int S[MAX];
    int top_value = -1;
    int *top = &top_value;

    while (1) {
        printf("Options:\n");
        printf("[0] Exit\n");
        printf("[1] Push\n");
        printf("[2] Pop\n");
        printf("[3] Display\n");
        printf("[4] Underflow Check\n");
        printf("[5] Overflow Check\n");

        int option;
        printf("Enter Option to Execute:\n");
        scanf("%d", &option);

        printf("Running Operation...\n");
        switch (option) {
            case 0: {
                printf("Exiting System");
                exit(0);
                break;
            }
            case 1: {
                int x;
                printf("Enter Element to push: \n");
                scanf("%d", &x);
                push(S, top, x);
                break;
            }
            case 2: {
                pop(S, top);
                break;
            }
            case 3: {
                printf("Displaying Stack...\n");
                display(S, top);
                break;
            }
            case 4: {
                int status;
                status = IsEmpty(S, top);
                if (status == 1) {
                    printf("Stack Underflow!");
                }
                break;
            }
            case 5: {
                int status;
                status = IsFull(S, top);
                if (status == 1) {
                    printf("Stack Overflow!");
                }
                break;
            }
        }
    }
    return 0;
}