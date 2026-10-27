#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    int coeff;
    int exp;
    struct Term *next;
} Term;

Term *createNode(int coeff, int exp) {
    Term *node = (Term *)malloc(sizeof(Term));
    if (!node) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    node->coeff = coeff;
    node->exp = exp;
    node->next = node;
    return node;
}

void insertTerm(Term **tail, int coeff, int exp) {
    Term *p;
    if (coeff == 0) return;
    if (!*tail) {
        *tail = createNode(coeff, exp);
        return;
    }
    p = (*tail)->next;
    do {
        if (p->exp == exp) {
            p->coeff += coeff;
            return;
        }
        p = p->next;
    } while (p != (*tail)->next);
    {
        Term *node = createNode(coeff, exp);
        node->next = (*tail)->next;
        (*tail)->next = node;
        *tail = node;
    }
}

Term *createPolynomial(void) {
    Term *tail = NULL;
    int n, i, coeff, exp;
    printf("Enter number of terms: ");
    scanf("%d", &n);
    if (n < 0) n = 0;
    for (i = 0; i < n; i++) {
        printf("Enter coefficient and exponent: ");
        scanf("%d%d", &coeff, &exp);
        insertTerm(&tail, coeff, exp);
    }
    return tail;
}

void displayPolynomial(Term *tail) {
    Term *p;
    int first = 1;
    if (!tail) {
        printf("0\n");
        return;
    }
    p = tail->next;
    do {
        if (p->coeff != 0) {
            if (!first && p->coeff > 0) printf(" + ");
            if (!first && p->coeff < 0) printf(" - ");
            if (first && p->coeff < 0) printf("-");
            if (abs(p->coeff) != 1 || p->exp == 0) printf("%d", abs(p->coeff));
            if (p->exp > 0) {
                printf("x");
                if (p->exp > 1) printf("^%d", p->exp);
            }
            first = 0;
        }
        p = p->next;
    } while (p != tail->next);
    if (first) printf("0");
    printf("\n");
}

Term *addPolynomials(Term *a, Term *b) {
    Term *result = NULL, *p;
    if (a) {
        p = a->next;
        do {
            insertTerm(&result, p->coeff, p->exp);
            p = p->next;
        } while (p != a->next);
    }
    if (b) {
        p = b->next;
        do {
            insertTerm(&result, p->coeff, p->exp);
            p = p->next;
        } while (p != b->next);
    }
    if (result) {
        Term *prev = result, *cur = result->next;
        while (cur != result) {
            if (cur->coeff == 0) {
                prev->next = cur->next;
                if (cur == result) result = prev;
                free(cur);
                cur = prev->next;
            } else {
                prev = cur;
                cur = cur->next;
            }
        }
        if (result->coeff == 0) {
            if (result->next == result) {
                free(result);
                result = NULL;
            } else {
                Term *last = result;
                while (last->next != result) last = last->next;
                last->next = result->next;
                p = result;
                result = last;
                free(p);
            }
        }
    }
    return result;
}

void freePolynomial(Term **tail) {
    Term *head, *p, *next;
    if (!*tail) return;
    head = (*tail)->next;
    p = head->next;
    while (p != head) {
        next = p->next;
        free(p);
        p = next;
    }
    free(head);
    *tail = NULL;
}

int main(void) {
    Term *p1 = NULL, *p2 = NULL, *sum = NULL;
    int choice;
    do {
        printf("\n1. Create polynomial 1\n2. Create polynomial 2\n3. Display polynomials\n4. Add polynomials\n0. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                freePolynomial(&p1);
                p1 = createPolynomial();
                break;
            case 2:
                freePolynomial(&p2);
                p2 = createPolynomial();
                break;
            case 3:
                printf("P1 = ");
                displayPolynomial(p1);
                printf("P2 = ");
                displayPolynomial(p2);
                break;
            case 4:
                freePolynomial(&sum);
                sum = addPolynomials(p1, p2);
                printf("Sum = ");
                displayPolynomial(sum);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
    freePolynomial(&p1);
    freePolynomial(&p2);
    freePolynomial(&sum);
    return 0;
}
