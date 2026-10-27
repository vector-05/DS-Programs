#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int regNo;
    char name[80];
    struct Student *next;
} Student;

Student *head = NULL;

Student *createStudent(int regNo, const char name[]) {
    Student *node = (Student *)malloc(sizeof(Student));
    if (!node) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    node->regNo = regNo;
    strcpy(node->name, name);
    node->next = NULL;
    return node;
}

void addStudent(void) {
    int regNo;
    char name[80];
    Student *p;
    printf("Enter registration number: ");
    scanf("%d", &regNo);
    for (p = head; p; p = p->next)
        if (p->regNo == regNo) {
            printf("Registration number already exists.\n");
            return;
        }
    printf("Enter name: ");
    scanf(" %79[^\n]", name);
    {
        Student *node = createStudent(regNo, name);
        if (!head || regNo < head->regNo) {
            node->next = head;
            head = node;
        } else {
            p = head;
            while (p->next && p->next->regNo < regNo)
                p = p->next;
            node->next = p->next;
            p->next = node;
        }
    }
    printf("Student added.\n");
}

void removeStudent(void) {
    int regNo;
    Student *p = head, *prev = NULL;
    printf("Enter registration number to remove: ");
    scanf("%d", &regNo);
    while (p && p->regNo != regNo) {
        prev = p;
        p = p->next;
    }
    if (!p) {
        printf("Student not found.\n");
        return;
    }
    if (prev) prev->next = p->next;
    else head = p->next;
    free(p);
    printf("Student removed.\n");
}

void displayStudents(void) {
    Student *p = head;
    if (!p) {
        printf("Enrollment list is empty.\n");
        return;
    }
    printf("RegNo\tName\n");
    while (p) {
        printf("%d\t%s\n", p->regNo, p->name);
        p = p->next;
    }
}

int countStudents(void) {
    int count = 0;
    Student *p;
    for (p = head; p; p = p->next) count++;
    return count;
}

void sortStudents(void) {
    Student *p, *q;
    if (!head) return;
    for (p = head; p; p = p->next)
        for (q = p->next; q; q = q->next)
            if (p->regNo > q->regNo) {
                int tempReg = p->regNo;
                char tempName[80];
                strcpy(tempName, p->name);
                p->regNo = q->regNo;
                strcpy(p->name, q->name);
                q->regNo = tempReg;
                strcpy(q->name, tempName);
            }
    printf("List sorted by registration number.\n");
}

void reverseStudents(void) {
    Student *prev = NULL, *current = head, *next;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    printf("List reversed.\n");
}

int main(void) {
    int choice;
    do {
        printf("\n1. Add student\n2. Remove student\n3. Display list\n4. Count students\n5. Sort list\n6. Reverse list\n0. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addStudent(); break;
            case 2: removeStudent(); break;
            case 3: displayStudents(); break;
            case 4: printf("Total students: %d\n", countStudents()); break;
            case 5: sortStudents(); break;
            case 6: reverseStudents(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    while (head) {
        Student *temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}
