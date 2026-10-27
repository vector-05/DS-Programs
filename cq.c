#include <stdio.h>
#define MAX 50

typedef struct {
    int jobId;
    char title[100];
} PrintJob;

PrintJob queue[MAX];
int front = 0, rear = -1, count = 0;

void enqueue(void) {
    PrintJob job;
    int i, index;
    if (count == MAX) {
        printf("Queue is full.\n");
        return;
    }
    printf("Enter Job ID: ");
    scanf("%d", &job.jobId);
    for (i = 0; i < count; i++) {
        index = (front + i) % MAX;
        if (queue[index].jobId == job.jobId) {
            printf("Job ID already exists in pending queue.\n");
            return;
        }
    }
    printf("Enter document title: ");
    scanf(" %99[^\n]", job.title);
    rear = (rear + 1) % MAX;
    queue[rear] = job;
    count++;
    printf("Print job added.\n");
}

void dequeue(void) {
    if (count == 0) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Processing Job ID %d: %s\n", queue[front].jobId, queue[front].title);
    front = (front + 1) % MAX;
    count--;
    if (count == 0) {
        front = 0;
        rear = -1;
    }
}

void display(void) {
    int i, index;
    if (count == 0) {
        printf("No pending print jobs.\n");
        return;
    }
    printf("Job ID\tDocument Title\n");
    for (i = 0; i < count; i++) {
        index = (front + i) % MAX;
        printf("%d\t%s\n", queue[index].jobId, queue[index].title);
    }
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
