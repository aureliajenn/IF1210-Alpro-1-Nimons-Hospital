#ifndef QUEUE_H
#define QUEUE_H

typedef struct Pasien {
    int id;
    char nama[100];
    char riwayat_penyakit[50];
    float suhu_tubuh;
    int tekanan_darah_sistolik;
    int tekanan_darah_diastolik;
    int detak_jantung;
    float saturasi_oksigen;
    int kadar_gula_darah;
    float berat_badan;
    int tinggi_badan;
    int kadar_kolesterol;
    int kadar_kolesterol_ldl;
    int trombosit;
} Pasien;

typedef struct QueueNode {
    Pasien patient;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;

// Function prototypes for queue operations
Queue* createQueue();
void enqueue(Queue *q, Pasien p);
Pasien dequeue(Queue *q);
int isQueueEmpty(Queue *q);
void printQueue(Queue *q);
void clearQueue(Queue *q);
int getQueuePosition(Queue *q, int id);

#endif
