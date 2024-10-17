#include <stdio.h>
#include <stdlib.h>

// Define the structure for a stack node
struct Node {
    int data;
    struct Node* next;
};

// Define the structure for the stack
struct Stack {
    struct Node* top;
};

// Function to create a new stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) { // Check if memory allocation was successful
        printf("Memory allocation failed\n");
        exit(1); // Exit if allocation fails
    }
    stack->top = NULL;
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Function to push an element onto the stack
void push(struct Stack* stack, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) { // Check if memory allocation was successful
        printf("Memory allocation failed\n");
        exit(1); // Exit if allocation fails
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
    printf("%d pushed to stack\n", data);
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return -1; // Return an error value
    }
    struct Node* temp = stack->top;
    int poppedValue = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return poppedValue;
}

// Function to peek at the top element of the stack
int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1; // Return an error value
    }
    return stack->top->data;
}

// Function to display all elements in the stack
void displayStack(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    
    struct Node* temp = stack->top;
    printf("Stack elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to demonstrate stack operations
int main() {
    struct Stack* stack = createStack();

    push(stack, 20);
    push(stack, 40);
    push(stack, 60);

    displayStack(stack); // Display all stack elements

    printf("%d popped from stack\n", pop(stack));
    printf("Top element is %d\n", peek(stack));

    displayStack(stack); // Display stack after a pop

    // Free remaining nodes
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack); // Free the stack structure

    return 0;
}

