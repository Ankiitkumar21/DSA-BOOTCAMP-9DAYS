#include <stdio.h>
#include <stdlib.h>

// Define the structure for a circular queue node
struct Node {
    int data;
    struct Node* next;
};

// Define the structure for the circular queue
struct CircularQueue {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new circular queue
struct CircularQueue* createCircularQueue() {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    if (!queue) {  // Check for memory allocation failure
        printf("Memory allocation failed\n");
        exit(1);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the circular queue is empty
int isEmptyCircular(struct CircularQueue* queue) {
    return queue->front == NULL;
}

// Function to enqueue an element in circular queue
void enqueueCircular(struct CircularQueue* queue, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {  // Check for memory allocation failure
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;

    if (isEmptyCircular(queue)) {
        queue->front = queue->rear = newNode;
        newNode->next = newNode; // Point to itself, making it circular
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
        newNode->next = queue->front; // Maintain the circular nature
    }
    printf("%d enqueued to circular queue\n", data);
}

// Function to dequeue an element from circular queue
int dequeueCircular(struct CircularQueue* queue) {
    if (isEmptyCircular(queue)) {
        printf("Circular queue underflow\n");
        return -1; // Return an error value
    }

    struct Node* temp = queue->front;
    int dequeuedValue = temp->data;

    if (queue->front == queue->rear) { // Only one node in the queue
        queue->front = queue->rear = NULL; // Queue becomes empty
    } else {
        queue->front = queue->front->next;
        queue->rear->next = queue->front; // Maintain circular nature
    }

    free(temp);
    return dequeuedValue;
}

// Function to peek at the front element of the circular queue
int peekCircular(struct CircularQueue* queue) {
    if (isEmptyCircular(queue)) {
        printf("Circular queue is empty\n");
        return -1; // Return an error value
    }
    return queue->front->data;
}

// Function to display elements of the circular queue
void displayCircularQueue(struct CircularQueue* queue) {
    if (isEmptyCircular(queue)) {
        printf("Circular queue is empty\n");
        return;
    }

    struct Node* temp = queue->front;
    printf("Circular Queue: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != queue->front);
    printf("\n");
}

// Main function to demonstrate circular queue operations
int main() {
    struct CircularQueue* queue = createCircularQueue();

    enqueueCircular(queue, 20);
    enqueueCircular(queue, 30);
    enqueueCircular(queue, 40);

    displayCircularQueue(queue); // Display the queue

    printf("%d dequeued from circular queue\n", dequeueCircular(queue));
    displayCircularQueue(queue); // Display the queue after dequeue

    printf("Front element is %d\n", peekCircular(queue));

    // Free remaining nodes
    while (!isEmptyCircular(queue)) {
        dequeueCircular(queue);
    }
    free(queue); // Free the queue structure

    return 0;
}

