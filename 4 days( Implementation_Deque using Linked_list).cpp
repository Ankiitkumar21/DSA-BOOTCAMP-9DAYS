#include <stdio.h>
#include <stdlib.h>

// Define the structure for a deque node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Define the structure for the deque
struct Deque {
    struct Node* front;
    struct Node* rear;
    int size;  // Track the size of the deque
};

// Function to create a new deque
struct Deque* createDeque() {
    struct Deque* deque = (struct Deque*)malloc(sizeof(struct Deque));
    if (!deque) { // Memory allocation check
        printf("Memory allocation failed\n");
        exit(1);
    }
    deque->front = deque->rear = NULL;
    deque->size = 0;  // Initialize size to 0
    return deque;
}

// Function to check if the deque is empty
int isEmptyDeque(struct Deque* deque) {
    return deque->front == NULL;
}

// Function to get the size of the deque
int getSize(struct Deque* deque) {
    return deque->size;
}

// Function to insert an element at the front of the deque
void insertFront(struct Deque* deque, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {  // Memory allocation check
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = deque->front;
    newNode->prev = NULL;

    if (isEmptyDeque(deque)) {
        deque->rear = newNode;
    } else {
        deque->front->prev = newNode;
    }

    deque->front = newNode;
    deque->size++;  // Increase deque size
    printf("%d inserted at front of deque\n", data);
}

// Function to insert an element at the rear of the deque
void insertRear(struct Deque* deque, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {  // Memory allocation check
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = deque->rear;

    if (isEmptyDeque(deque)) {
        deque->front = newNode;
    } else {
        deque->rear->next = newNode;
    }

    deque->rear = newNode;
    deque->size++;  // Increase deque size
    printf("%d inserted at rear of deque\n", data);
}

// Function to delete an element from the front of the deque
int deleteFront(struct Deque* deque) {
    if (isEmptyDeque(deque)) {
        printf("Deque underflow\n");
        return -1; // Return an error value
    }

    struct Node* temp = deque->front;
    int deletedValue = temp->data;
    deque->front = deque->front->next;

    if (deque->front == NULL) {
        deque->rear = NULL; // Deque becomes empty
    } else {
        deque->front->prev = NULL;
    }

    free(temp);
    deque->size--;  // Decrease deque size
    return deletedValue;
}

// Function to delete an element from the rear of the deque
int deleteRear(struct Deque* deque) {
    if (isEmptyDeque(deque)) {
        printf("Deque underflow\n");
        return -1; // Return an error value
    }

    struct Node* temp = deque->rear;
    int deletedValue = temp->data;
    deque->rear = deque->rear->prev;

    if (deque->rear == NULL) {
        deque->front = NULL; // Deque becomes empty
    } else {
        deque->rear->next = NULL;
    }

    free(temp);
    deque->size--;  // Decrease deque size
    return deletedValue;
}

// Function to peek at the front element of the deque
int peekFront(struct Deque* deque) {
    if (isEmptyDeque(deque)) {
        printf("Deque is empty\n");
        return -1; // Return an error value
    }
    return deque->front->data;
}

// Function to peek at the rear element of the deque
int peekRear(struct Deque* deque) {
    if (isEmptyDeque(deque)) {
        printf("Deque is empty\n");
        return -1; // Return an error value
    }
    return deque->rear->data;
}

// Function to display elements of the deque
void displayDeque(struct Deque* deque) {
    if (isEmptyDeque(deque)) {
        printf("Deque is empty\n");
        return;
    }
    
    struct Node* temp = deque->front;
    printf("Deque: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to demonstrate deque operations
int main() {
    struct Deque* deque = createDeque();

    insertRear(deque, 10);
    insertRear(deque, 25);
    insertFront(deque, 5);
    insertFront(deque, 2);

    displayDeque(deque); // Display the deque contents
    printf("Deque size: %d\n", getSize(deque)); // Display deque size

    printf("%d deleted from front of deque\n", deleteFront(deque));
    displayDeque(deque);
    printf("Front element is %d\n", peekFront(deque));
    printf("Rear element is %d\n", peekRear(deque));

    printf("%d deleted from rear of deque\n", deleteRear(deque));
    displayDeque(deque);
    printf("Deque size: %d\n", getSize(deque)); // Display deque size

    // Free remaining nodes
    while (!isEmptyDeque(deque)) {
        deleteFront(deque);
    }
    free(deque); // Free the deque structure

    return 0;
}

