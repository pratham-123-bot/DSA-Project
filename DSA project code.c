#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[20];
    int age;
    int severity;  // 1 = Mild, 2 = Moderate, 3 = Severe
} Patient;

// Function to add a patient to the stack
void addPatient(Patient stack[], int *top) {
    if (*top == MAX - 1) {
        printf("The stack is full! Cannot add more patients.\n");
        return;
    }
    
    char name[20];
    int age, severity;
    
    printf("Enter patient name: ");
    scanf("%s", name);
    printf("Enter patient age: ");
    scanf("%d", &age);
    printf("Enter severity (1 = Mild, 2 = Moderate, 3 = Severe): ");
    scanf("%d", &severity);
    
    if (severity < 1 || severity > 3) {
        printf("Invalid severity! Please enter a value between 1 and 3.\n");
        return;
    }
    
    (*top)++;
    stack[*top] = (Patient){.name = "", .age = age, .severity = severity};
    strcpy(stack[*top].name, name);
    printf("Patient '%s' added successfully!\n", name);
}

// Function to prioritize the most severe patient
void prioritizePatient(Patient stack[], int top) {
    int index = top;
    for (int i = top - 1; i >= 0; i--) {
        if (stack[i].severity > stack[index].severity) {
            index = i;
        }
    }
    // Swap the most severe patient with the patient at the top
    if (index != top) {
        Patient temp = stack[top];
        stack[top] = stack[index];
        stack[index] = temp;
    }
}

// Function to treat the top patient from the stack
void treatPatient(Patient stack[], int *top) {
    if (*top == -1) {
        printf("No patients left to treat.\n");
        return;
    }
    
    prioritizePatient(stack, *top);  // Ensure the most severe patient is at the top
    printf("Treating %s (Age: %d, Severity: %d)\n", stack[*top].name, stack[*top].age, stack[*top].severity);
    (*top)--;
}

int main() {
    Patient stack[MAX];
    int top = -1;
    int choice;
    
    while (1) {
        printf("\n--- Emergency Room Menu ---\n");
        printf("1. Add Patient\n");
        printf("2. Treat Patient\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addPatient(stack, &top);
                break;
                
            case 2:
                treatPatient(stack, &top);
                break;
                
            case 3:
                printf("Exiting... Have a great day!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}