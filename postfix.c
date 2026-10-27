#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define MAX 256

int main(void) {
    char expr[MAX];
    double stack[MAX], a, b;
    int top = -1, i, valid = 1;
    printf("Enter postfix expression using single-digit operands: ");
    scanf("%255s", expr);
    for (i = 0; expr[i]; i++) {
        char c = expr[i];
        if (isspace((unsigned char)c)) continue;
        if (isdigit((unsigned char)c)) {
            stack[++top] = c - '0';
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') {
            if (top < 1) {
                valid = 0;
                break;
            }
            b = stack[top--];
            a = stack[top--];
            if ((c == '/' || c == '%') && b == 0) {
                printf("Division by zero is not allowed.\n");
                return 1;
            }
            switch (c) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = a / b; break;
                case '%': stack[++top] = (int)a % (int)b; break;
                case '^': stack[++top] = pow(a, b); break;
            }
        } else {
            valid = 0;
            break;
        }
    }
    if (!valid || top != 0) {
        printf("Invalid postfix expression.\n");
        return 1;
    }
    printf("Result: %.2f\n", stack[top]);
    return 0;
}
