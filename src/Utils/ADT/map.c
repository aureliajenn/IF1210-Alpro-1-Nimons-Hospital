#include "Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
        exit(1);
    }
    return map;
}

void insertDoctor(Map *map, Dokter *doctor) {
    if (map->size >= map->capacity) {
        printf("Map is full, cannot insert more doctors.\n");
        return;
    }
    map->dokter[map->size++] = doctor;
}

Dokter* getDoctor(Map *map, int id) {
    for (int i = 0; i < map->size; i++) {
        if (map->dokter[i]->id == id) {
            return map->dokter[i];
        }
    }
    return NULL;
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
