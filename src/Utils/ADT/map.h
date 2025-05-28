#ifndef MAP_H
#define MAP_H

#include "Queue.h"
#include "../Model/model.h"

typedef struct Dokter {
    int id;
    int ruangan;        // Ruangan dokter
    Queue *queue;         // Queue pasien untuk dokter ini
    int jumlahPasienDalamRuangan; // Kapasitas maksimal pasien di dalam ruangan
    int jumlahPasienLuarRuangan;   // Kapasitas maksimal antrian di luar ruangan
    int queueLength;  // Jumlah pasien yang sedang menunggu di luar
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
void insertDoctor(Map *map, Dokter *doctor);
Dokter* getDoctor(Map *map,  int id);
void printMap(Map *map);
void clearMap(Map *map);

#endif
