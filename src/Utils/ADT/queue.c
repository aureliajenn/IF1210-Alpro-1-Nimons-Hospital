#include "main.h"

Queue* createQueue() {
    Queue *q = malloc(sizeof(Queue));
    if (q == NULL) {
        perror("Failed to allocate memory for queue");
        exit(1);
    }
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

void enqueue(Queue *q, User p) {
    if (q == NULL) {
        printf("Queue tidak diinisialisasi!\n");
        return;
    }
  

    QueueNode *newNode = malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        perror("Failed to allocate memory for queue node");
        exit(1);
    }
    newNode->patient = p;
    newNode->next = NULL;

    
    if (q->rear == NULL) {

        q->front = q->rear = newNode;  
    } else {

        q->rear->next = newNode;  
        q->rear = newNode;      
    }
    q->size++;
}


User dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        perror("Queue is empty, cannot dequeue");
        exit(1);
    }
    
    QueueNode *temp = q->front;
    User dequeuedPatient = temp->patient;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->size--;
    return dequeuedPatient;
}

int isQueueEmpty(Queue *q) {
    return q->size == 0;
}

void printQueue(Queue *q) {
    QueueNode *current = q->front;
    while (current != NULL) {
        printf("id User: %d, Nama: %s, Suhu Tubuh: %f, Sistolik: %d, Diastolik: %d, Detak Jantung: %d\n",
               current->patient.identitas.id, current->patient.identitas.username, current->patient.kondisi.suhu_tubuh,
               current->patient.kondisi.tekanan_darah_sistolik, current->patient.kondisi.tekanan_darah_diastolik,
               current->patient.kondisi.detak_jantung);
        current = current->next;
    }
}

void clearQueue(Queue *q) {
    while (!isQueueEmpty(q)) {
        dequeue(q);
    }
    free(q);
}

int getQueuePosition(Queue *q, int id) {
    if (q == NULL || q->front == NULL) {
        printf("Queue is empty or uninitialized!\n");
        return -1; 
    }
    
    QueueNode *current = q->front;
    int position = 1;
    
    while (current != NULL) {
        if (current->patient.identitas.id == id) {
            return position; 
        }
        current = current->next;
        position++;
    }
    
    return -1;
}
