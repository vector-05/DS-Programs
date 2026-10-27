#include <stdio.h>
#include <string.h>
#define MAX 50

typedef struct {
    int jobId;
    char title[100];
} PrintJob;

PrintJob queue[MAX];
int count = 0;

void enqueue(void) {
    PrintJob job;
    int i;
    if (count == MAX) {
        printf("Queue is full.\n");
        return;
    }
    printf("Enter Job ID: ");
    scanf("%d", &job.jobId);
    for (i = 0; i < count; i++)
        if (queue[i].jobId == job.jobId) {
            printf("Job ID already exists in pending queue.\n");
            return;
        }
    printf("Enter document title: ");
    scanf(" %99[^\n]", job.title);
    queue[count++] = job;
    printf("Print job added.\n");
}

void dequeue(void) {
    int i;
    if (count == 0) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Processing Job ID %d: %s\n", queue[0].jobId, queue[0].title);
    for (i = 1; i < count; i++)
        queue[i - 1] = queue[i];
    count--;
}

void display(void) {
    int i;
    if (count == 0) {
        printf("No pending print jobs.\n");
        return;
    }
    printf("Job ID\tDocument Title\n");
    for (i = 0; i < count; i++)
        printf("%d\t%s\n", queue[i].jobId, queue[i].title);
}

int main(void) {
    int choice;
    do {
        printf("\n1. Add print job\n2. Process print job\n3. Display pending jobs\n0. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: display(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}
