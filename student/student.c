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

// insertion sort
void insertion_sort(struct student A[], int n) {
    for (int i = 1; i < n; i++) {
        struct student key = A[i]; 
        int j = i - 1;

        while (j >= 0 && A[j].rollno > key.rollno) {
            A[j + 1] = A[j];       
            j = j - 1;
        }
        
        A[j + 1] = key;  
    }
}

// selection sort
void selection_sort(struct student A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (A[j].rollno < A[minIndex].rollno) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            struct student temp = A[i];
            A[i] = A[minIndex];
            A[minIndex] = temp;
        }
    }
}

// shell sort
void shell_sort(struct student A[], int n) {
    if (n <= 1) return; 
        int gap = n / 2;
        do {
            int i = gap;
            do {
                struct student temp = A[i];
                int j = i;

                if (j >= gap && A[j - gap].rollno > temp.rollno) {
                    do {
                        A[j] = A[j - gap];
                        j -= gap;
                    } while (j >= gap && A[j - gap].rollno > temp.rollno);
                }

                A[j] = temp;
                i++;

            } while (i < n);

            gap /= 2;

        } while (gap > 0);
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
    printf("[3] Insertion Sort\n");
    printf("[4] Selection Sort\n");
    printf("[5] Shell Sort\n");
    printf("[6] Display Records\n");
    printf("[0] Exit\n");
    
    int ch;
    printf("Enter choice: ");
    scanf(" %d", &ch);
    
    // sorted flag
    int is_sorted = 0;

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
    
    case 3: {
        // insertion sort
        if (is_sorted == 1) {
            printf("List Already Sorted...\n");
            break;
        } else {
            insertion_sort(students, n);
            printf("List has been sorted...\n");
            is_sorted = 1;
            break;
        }
    }
    
    case 4: {
        // selection sort
        if (is_sorted == 1) {
            printf("List Already Sorted...\n");
            break;
        } else {
            selection_sort(students, n);
            printf("List has been sorted...\n");
            is_sorted = 1;
            break;
        }
    }
    
    case 5: {
        // shell sort
        if (is_sorted == 1) {
            printf("List Already Sorted...\n");
            break;
        } else {
            shell_sort(students, n);
            printf("List has been sorted...\n");
            is_sorted = 1;
            break;
        }
    }

    case 6: {
        // display records
        printf("Displaying Records...\n");
        display(n);
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