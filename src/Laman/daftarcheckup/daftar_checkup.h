#ifndef DAFTAR_CHECKUP_H
#define DAFTAR_CHECKUP_H

#define MAX_NAME 50

#include "queue.h"

typedef struct {
    char nama_dokter[MAX_NAME];
    char ruangan[MAX_NAME];
    Queue queue;
} Dokter;

typedef struct {
    char nama_pasien[MAX_NAME];
    char nama_dokter[MAX_NAME];
} MapPasien;

void daftar_checkup(const char* pasien, Dokter* dokter_list, int jumlah_dokter, MapPasien* map, int* jumlah_map);

#endif