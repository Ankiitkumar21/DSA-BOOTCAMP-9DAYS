#include <stdio.h>
#include <stdlib.h>

// Define the structure for a queue node
struct Node {
    int data;
    struct Node* next;
};

// Define the structure for the queue
struct Queue {
    struct Node* front;
    struct Node* rear;
    int size;  // Added to track the size of the queue
};

// Function to create a new queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (!queue) {
        printf("Memory allocation failed\n");
        exit(1); // Exit if allocation fails
    }
    queue->front = queue->rear = NULL;
    queue->size = 0; // Initialize size to 0
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to get the size of the queue
int getSize(struct Queue* queue) {
    return queue->size;
}

// Function to enqueue an element
void enqueue(struct Queue* queue, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1); // Exit if allocation fails
    }
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    queue->size++; // Increase the size of the queue
    printf("%d enqueued to queue\n", data);
}

// Function to dequeue an element
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        return -1; // Return an error value
    }

    struct Node* temp = queue->front;
    int dequeuedValue = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--; // Decrease the size of the queue
    return dequeuedValue;
}

// Function to peek at the front element of the queue
int peek(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1; // Return an error value
    }
    return queue->front->data;
}

// Function to display the queue elements
void displayQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    struct Node* temp = queue->front;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to demonstrate queue operations
int main() {
    struct Queue* queue = createQueue();

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    displayQueue(queue);
    printf("Queue size: %d\n", getSize(queue));

    printf("%d dequeued from queue\n", dequeue(queue));
    displayQueue(queue);
    printf("Front element is %d\n", peek(queue));
    printf("Queue size: %d\n", getSize(queue));

    // Free remaining nodes
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue); // Free the queue structure

    return 0;
}
