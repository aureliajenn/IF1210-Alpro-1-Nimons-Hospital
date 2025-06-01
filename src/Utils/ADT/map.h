#pragma once

#include "queue.h"
#include <stdbool.h>

typedef struct Dokter {
    int id;
    int ruangan;        // Ruangan dokter
    Queue *queue;         // Queue diagnosis untuk dokter ini
    Queue *queueNg;         // Queue ngobatin untuk dokter ini
    int jumlahPasienDalamRuangan; // Kapasitas maksimal pasien di dalam ruangan
    int jumlahPasienLuarRuangan;   // Kapasitas maksimal antrian di luar ruangan
    int queueLength;  // Jumlah antrian pasien diagnosis
    int queueLengthNg;  // Jumlah antrian pasien diagnosis
} Dokter;

typedef struct Map {
    Dokter **dokter;     // Array dari dokter
    int size;             // Jumlah dokter yang terdaftar
    int capacity;         // Kapasitas map
    int rows;            // Jumlah baris
    int cols;            // Jumlah kolom
    int maxPasienDalamRuangan; // Kapasitas maksimal pasien di dalam ruangan
    int maxAntrianLuar;   // Kapasitas maksimal antrian di luar ruangan
} Map;

// Prototipe fungsi Map
Map* createMap(int capacity);
int insertDoctor(Map *map, Dokter *doctor) ;
Dokter* getDoctor(Map *map,  int id);
void printMap(Map *map);
void clearMap(Map *map);
bool queueContains(Queue *q, int patientId) ;
Dokter* getDoctorByIdPatient(Map *map, int patientId);