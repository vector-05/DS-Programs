
#include <stdio.h>
#include <string.h>

#define MAX 256

// Stack for storing expressions
char stack[MAX][MAX];
int top = -1;

void push(char value[]) {
    strcpy(stack[++top], value);
}

void pop(char value[]) {
    strcpy(value, stack[top--]);
}

// Check whether character is an operand
int isOperand(char c) {
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9');
}

// Check whether character is an operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' ||
           c == '/' || c == '%' || c == '^';
}

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/' || c == '%') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

// Stack for operators during infix conversion
char ops[MAX];
int otop = -1;

void pushOp(char c) {
    ops[++otop] = c;
}

char popOp() {
    return ops[otop--];
}

// Infix to Postfix
void infixToPostfix(char in[], char out[], int reverseMode) {
    int k = 0;
    otop = -1;

    for (int i = 0; in[i] != '\0'; i++) {
        char c = in[i];

        if (isOperand(c)) {
            out[k++] = c;
        }
        else if (c == '(') {
            pushOp(c);
        }
        else if (c == ')') {
            while (otop >= 0 && ops[otop] != '(')
                out[k++] = popOp();

            if (otop >= 0)
                popOp();
        }
        else if (isOperator(c)) {
            while (otop >= 0 && isOperator(ops[otop]) &&
                  (precedence(ops[otop]) > precedence(c) ||
                  (precedence(ops[otop]) == precedence(c) &&
                   (reverseMode ? c == '^' : c != '^')))) {
                out[k++] = popOp();
            }

            pushOp(c);
        }
    }

    while (otop >= 0)
        out[k++] = popOp();

    out[k] = '\0';
}

// Reverse expression and swap brackets
void reverse(char in[], char out[]) {
    int n = strlen(in);

    for (int i = 0; i < n; i++) {
        char c = in[n - 1 - i];

        if (c == '(') c = ')';
        else if (c == ')') c = '(';

        out[i] = c;
    }

    out[n] = '\0';
}

// Infix to Prefix
void infixToPrefix(char in[], char out[]) {
    char rev[MAX], post[MAX];

    reverse(in, rev);
    infixToPostfix(rev, post, 1);
    reverse(post, out);
}

// Postfix to Infix
void postfixToInfix(char in[], char out[]) {
    char a[MAX], b[MAX], temp[MAX];
    top = -1;

    for (int i = 0; in[i] != '\0'; i++) {
        char c = in[i];

        if (isOperand(c)) {
            temp[0] = c;
            temp[1] = '\0';
            push(temp);
        }
        else if (isOperator(c)) {
            pop(b);
            pop(a);

            sprintf(temp, "(%s%c%s)", a, c, b);
            push(temp);
        }
    }

    pop(out);
}

// Prefix to Infix
void prefixToInfix(char in[], char out[]) {
    char a[MAX], b[MAX], temp[MAX];
    top = -1;

    for (int i = strlen(in) - 1; i >= 0; i--) {
        char c = in[i];

        if (isOperand(c)) {
            temp[0] = c;
            temp[1] = '\0';
            push(temp);
        }
        else if (isOperator(c)) {
            pop(a);
            pop(b);

            sprintf(temp, "(%s%c%s)", a, c, b);
            push(temp);
        }
    }

    pop(out);
}

// Prefix to Postfix
void prefixToPostfix(char in[], char out[]) {
    char a[MAX], b[MAX], temp[MAX];
    top = -1;

    for (int i = strlen(in) - 1; i >= 0; i--) {
        char c = in[i];

        if (isOperand(c)) {
            temp[0] = c;
            temp[1] = '\0';
            push(temp);
        }
        else if (isOperator(c)) {
            pop(a);
            pop(b);

            sprintf(temp, "%s%s%c", a, b, c);
            push(temp);
        }
    }

    pop(out);
}

// Postfix to Prefix
void postfixToPrefix(char in[], char out[]) {
    char a[MAX], b[MAX], temp[MAX];
    top = -1;

    for (int i = 0; in[i] != '\0'; i++) {
        char c = in[i];

        if (isOperand(c)) {
            temp[0] = c;
            temp[1] = '\0';
            push(temp);
        }
        else if (isOperator(c)) {
            pop(b);
            pop(a);

            sprintf(temp, "%c%s%s", c, a, b);
            push(temp);
        }
    }

    pop(out);
}

int main() {
    int choice;
    char in[MAX], out[MAX];

    do {
        printf("\n1. Infix to Postfix");
        printf("\n2. Infix to Prefix");
        printf("\n3. Prefix to Postfix");
        printf("\n4. Prefix to Infix");
        printf("\n5. Postfix to Infix");
        printf("\n6. Postfix to Prefix");
        printf("\n0. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 6) {
            printf("Enter expression: ");
            scanf("%255s", in);

            switch (choice) {
                case 1:
                    infixToPostfix(in, out, 0);
                    break;
                case 2:
                    infixToPrefix(in, out);
                    break;
                case 3:
                    prefixToPostfix(in, out);
                    break;
                case 4:
                    prefixToInfix(in, out);
                    break;
                case 5:
                    postfixToInfix(in, out);
                    break;
                case 6:
                    postfixToPrefix(in, out);
                    break;
            }

            printf("Result: %s\n", out);
        }
        else if (choice != 0) {
            printf("Invalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}
