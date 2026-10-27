#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 256

typedef struct {
    char data[MAX][MAX];
    int top;
} Stack;

void initStack(Stack *s) { s->top = -1; }
int empty(Stack *s) { return s->top == -1; }
void push(Stack *s, const char *value) {
    if (s->top < MAX - 1) strcpy(s->data[++s->top], value);
}
void pop(Stack *s, char *value) {
    if (empty(s)) value[0] = '\0';
    else strcpy(value, s->data[s->top--]);
}
int isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^'; }
int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/' || c == '%') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

void infixToPostfix(const char *in, char *out, int reverseMode) {
    char ops[MAX];
    int top = -1, i, k = 0;
    for (i = 0; in[i]; i++) {
        char c = in[i];
        if (isspace((unsigned char)c)) continue;
        if (isalnum((unsigned char)c)) out[k++] = c;
        else if (c == '(') ops[++top] = c;
        else if (c == ')') {
            while (top >= 0 && ops[top] != '(') out[k++] = ops[top--];
            if (top >= 0) top--;
        } else if (isOperator(c)) {
            while (top >= 0 && isOperator(ops[top]) &&
                   (reverseMode ? precedence(ops[top]) > precedence(c) : precedence(ops[top]) > precedence(c) ||
                    (precedence(ops[top]) == precedence(c) && c != '^')))
                out[k++] = ops[top--];
            ops[++top] = c;
        }
    }
    while (top >= 0) {
        if (ops[top] != '(') out[k++] = ops[top];
        top--;
    }
    out[k] = '\0';
}

void reverseAndSwap(const char *src, char *dst) {
    int i, n = (int)strlen(src);
    for (i = 0; i < n; i++) {
        char c = src[n - 1 - i];
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
        dst[i] = c;
    }
    dst[n] = '\0';
}

void infixToPrefix(const char *in, char *out) {
    char reversed[MAX], post[MAX];
    reverseAndSwap(in, reversed);
    infixToPostfix(reversed, post, 1);
    reverseAndSwap(post, out);
}

void postfixToInfix(const char *in, char *out) {
    Stack s;
    char a[MAX], b[MAX], temp[MAX];
    int i;
    initStack(&s);
    for (i = 0; in[i]; i++) {
        char c = in[i];
        if (isspace((unsigned char)c)) continue;
        if (isalnum((unsigned char)c)) {
            temp[0] = c; temp[1] = '\0'; push(&s, temp);
        } else if (isOperator(c)) {
            pop(&s, b); pop(&s, a);
            snprintf(temp, sizeof(temp), "(%s%c%s)", a, c, b);
            push(&s, temp);
        }
    }
    pop(&s, out);
}

void prefixToInfix(const char *in, char *out) {
    Stack s;
    char a[MAX], b[MAX], temp[MAX];
    int i;
    initStack(&s);
    for (i = (int)strlen(in) - 1; i >= 0; i--) {
        char c = in[i];
        if (isspace((unsigned char)c)) continue;
        if (isalnum((unsigned char)c)) {
            temp[0] = c; temp[1] = '\0'; push(&s, temp);
        } else if (isOperator(c)) {
            pop(&s, a); pop(&s, b);
            snprintf(temp, sizeof(temp), "(%s%c%s)", a, c, b);
            push(&s, temp);
        }
    }
    pop(&s, out);
}

void prefixToPostfix(const char *in, char *out) {
    Stack s;
    char a[MAX], b[MAX], temp[MAX];
    int i;
    initStack(&s);
    for (i = (int)strlen(in) - 1; i >= 0; i--) {
        char c = in[i];
        if (isspace((unsigned char)c)) continue;
        if (isalnum((unsigned char)c)) {
            temp[0] = c; temp[1] = '\0'; push(&s, temp);
        } else if (isOperator(c)) {
            pop(&s, a); pop(&s, b);
            snprintf(temp, sizeof(temp), "%s%s%c", a, b, c);
            push(&s, temp);
        }
    }
    pop(&s, out);
}

void postfixToPrefix(const char *in, char *out) {
    Stack s;
    char a[MAX], b[MAX], temp[MAX];
    int i;
    initStack(&s);
    for (i = 0; in[i]; i++) {
        char c = in[i];
        if (isspace((unsigned char)c)) continue;
        if (isalnum((unsigned char)c)) {
            temp[0] = c; temp[1] = '\0'; push(&s, temp);
        } else if (isOperator(c)) {
            pop(&s, b); pop(&s, a);
            snprintf(temp, sizeof(temp), "%c%s%s", c, a, b);
            push(&s, temp);
        }
    }
    pop(&s, out);
}

int main(void) {
    int choice;
    char in[MAX], out[MAX];
    do {
        printf("\n1. Infix to postfix\n2. Infix to prefix\n3. Prefix to postfix\n4. Prefix to infix\n5. Postfix to infix\n6. Postfix to prefix\n0. Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 6) {
            printf("Enter expression without spaces: ");
            scanf("%255s", in);
            switch (choice) {
                case 1: infixToPostfix(in, out, 0); break;
                case 2: infixToPrefix(in, out); break;
                case 3: prefixToPostfix(in, out); break;
                case 4: prefixToInfix(in, out); break;
                case 5: postfixToInfix(in, out); break;
                case 6: postfixToPrefix(in, out); break;
            }
            printf("Result: %s\n", out);
        } else if (choice != 0) printf("Invalid choice.\n");
    } while (choice != 0);
    return 0;
}
