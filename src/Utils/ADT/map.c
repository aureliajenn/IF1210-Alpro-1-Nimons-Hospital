#include "main.h"

extern User *user;

Map* createMap(int capacity) {
    Map *map = malloc(sizeof(Map));
    if (map == NULL) {
        perror("Failed to allocate memory for map");
        exit(1);
    }
    map->capacity = capacity;
    map->size = 0;
    map->rows = 0;
    map->cols = 0;

    map->dokter = malloc(sizeof(Dokter*) * capacity);
    if (map->dokter == NULL) {
        perror("Failed to allocate memory for doctors array");
        free(map);
        exit(1);
    }

    for (int i = 0; i < capacity; i++) {
        map->dokter[i] = malloc(sizeof(Dokter));
        if (map->dokter[i] == NULL) {
            perror("Failed to allocate memory for dokter");
            // Bebaskan yang sudah dialokasikan sebelumnya
            for (int j = 0; j < i; j++) {
                free(map->dokter[j]);
            }
            free(map->dokter);
            free(map);
            exit(1);
        }
    }
    return map;
}


int insertDoctor(Map *map, Dokter *doctor) {
    if (map->size >= map->capacity) {
        printf("Map is full, cannot insert more doctors.\n");
        return 0; // gagal
    }
    map->dokter[map->size++] = doctor;
    return 1; // sukses
}

Dokter* getDoctor(Map *map, int id) {
    for (int i = 0; i < map->size; i++) {
        if (map->dokter[i]->id == id) {
            return map->dokter[i];
        }
    }
    return NULL;
}


bool queueContains(Queue *q, int patientId) {
    if (!q) return false;

    QueueNode *current = q->front;
    while (current != NULL) {
        if (current->patient->identitas.id == patientId) {
            return true;
        }
        current = current->next;
    }
    return false;
}

Dokter* getDoctorByIdPatient(Map *map, int patientId) {
    for (int i = 0; i < map->size; i++) {
        Dokter *dokter = map->dokter[i];
        if (queueContains(dokter->queue, patientId) || queueContains(dokter->queueNg, patientId)) {
            return dokter;
        }
    }
    return NULL; // Pasien tidak ditemukan di antrian dokter mana pun
}

void printMap(Map *map) {
    if (map == NULL || map->dokter == NULL) {
        printf("Map atau array dokter tidak valid.\n");
        return;
    }

    for (int i = 0; i < map->size; i++) {
        if (map->dokter[i] != NULL) {
            printf("ID: %d, Room: %d, Max Patients in Room: %d, Queue Length: %d\n",
                   map->dokter[i]->id, map->dokter[i]->ruangan,
                   map->dokter[i]->jumlahPasienDalamRuangan, map->dokter[i]->queueLength);
        } else {
            printf("Dokter di indeks %d tidak valid.\n", i);
        }
    }
}


void clearMap(Map *map) {
    for (int i = 0; i < map->size; i++) {
        clearQueue(map->dokter[i]->queue);
        free(map->dokter[i]);
    }
    free(map->dokter);
    free(map);
}
