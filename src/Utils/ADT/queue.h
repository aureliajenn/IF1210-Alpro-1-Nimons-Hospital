#pragma once

typedef struct QueueNode {
    User *patient;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;

// Function prototypes for queue operations
Queue* createQueue();
void enqueue(Queue *q, User *p);
User dequeue(Queue *q);
int isQueueEmpty(Queue *q);
void printQueue(Queue *q);
void clearQueue(Queue *q);
int getQueuePosition(Queue *q, int id);