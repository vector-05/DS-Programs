#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student  {
    int rollno;
    char name[10];
    float marks;
} students[20];

int input(int n) {
    
    // Input Data
    printf("Inputing data for %d student\n", n);
    
    for (int i = 0; i < n; i++) {
    
    printf("\n");
    printf("Student %d\n", i+1);
    
    printf("Roll No:");
    scanf("%d", &students[i].rollno);

    printf("Name:");
    scanf("%9s", students[i].name); 

    printf("Marks:");
    scanf("%f", &students[i].marks);
    }
    
    return 0;
}

int display(int n) {
    
    // display data
    printf("Displaying data for %d student\n", n);
    
    for (int i = 0; i < n; i++) {
    printf("\n");
    printf("Student %d\n", i+1);
    printf("Roll No: %d\n", students[i].rollno);
    printf("Name: %s\n", students[i].name);
    printf("Marks: %f\n", students[i].marks);
    }
    return 0;
}

// Search Algorithms

// linear search
int linear_search(int n, int key) {
    for (int i = 0; i < n; i++) {
    	if (students[i].rollno == key) {
    		return i;
    	}
    }
    return -1;
}

// binary search
int binary_search(int n, int key) {
	int low = 0;
	int high = n - 1;
	int mid;
	while (low <= high) {
		mid = floor((low + high) / 2);
		if (students[mid].rollno == key) {
			return mid;
		} else if (students[mid].rollno > key) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	return -1;
}

// Sorting Algorithms

int insertion_sort(int A[20], int n) {
	return 0;
}

// menu program
int main() {

    printf("Students Program\n");

    // number of students
    int n;
    printf("Enter the number of students (max::20) :");
    scanf("%d", &n);

    // validation check
    if (n <= 0) {
        printf("Program Terminated\n");
        return 0;
    }
    
    printf("\n");
    // input data
    input(n);
    
    printf("\n");
    // display data
    display(n);
    
    while (1) {
    
    // menu
    printf("\n");
    printf("Select Action to Perform\n");
    printf("[1] Linear Search\n");
    printf("[2] Binary Search\n");
    printf("[0] Exit\n");
    
    int ch;
    printf("Enter choice: ");
    scanf(" %d", &ch);
    
    switch (ch) {
    
    case 1: {
    	// linear search
    	int key;
    	printf("Input Rollno to search: ");
    	scanf("%d", &key);
    	
    	int index = linear_search(n, key);
    	if (index == -1) {
    		printf("Rollno Not Present\n");
    	} else {
    		printf("Record Present.....\n");
    		printf("Displaying Record.....\n");
    		printf("Rollno: %d\n", students[index].rollno);
    		printf("Name: %s\n", students[index].name);
    		printf("Marks: %f\n", students[index].marks);
    		}
    	break;
    	}
    
    case 2: {
    	// binary search
    	int key;
    	printf("Input Rollno to search: ");
    	scanf("%d", &key);
    	
    	int index = binary_search(n, key);
    	if (index == -1) {
    		printf("Rollno Not Present\n");
    	} else {
    		printf("Record Present.....\n");
    		printf("Displaying Record.....\n");
    		printf("Rollno: %d\n", students[index].rollno);
    		printf("Name: %s\n", students[index].name);
    		printf("Marks: %f\n", students[index].marks);
    		}
    	break;
    	}
    	
    case 0: {
	    // exit
	    return 0;
	    break;
    	}
    
    default: {
    	// exit on default
    	return 0;
    	break;
    	}
    }
      
    }

    return 0;
}