#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ngobatin.h"

int lamanNgobatin(){
    extern User *user;
    // extern Map *obatpenyakit;    // blm ada
    // extern int jumlah_obatpenyakit;    // blm ada
    extern Map *map;

    if (user == NULL || user->identitas.role == NULL)
    {
        printf("Anda belum login!\n");
        return 0;
    }

    if (strcmpIgnoreCase(user->identitas.role, "dokter") != 0)
    {
        printf("Hanya dokter yang dapat mengakses laman ini!\n");
        return 0;
    }

    // if (obatpenyakit == NULL || jumlah_obatpenyakit == 0)   //blm ada
    // {
    //     printf("Data obat-penyakit tidak ditemukan!\n");
    //     return 0;
    // }

    Dokter *dokter = getDoctor(map, user->identitas.id);
    if (dokter == NULL)
    {
        printf("Dokter tidak ditemukan!\n");
        return 0;
    }

    Pasien pasien = dokter->queue->front->patient;
    printf("Dokter sedang mengobati pasien %s.\n", pasien.nama);
    printf("[Auto-Prescription-2.0] Mengobati...\n");

    if (pasien.riwayat_penyakit == NULL) {
        printf("Pasien %s tidak memiliki riwayat penyakit.\n", pasien.nama);
        return 0;
    }
    // for (int i = 0; i < jumlah_obatpenyakit; i++){
    //     if (strcmp(pasien.riwayat_penyakit, obatpenyakit->penyakit[i]) == 0){        //blm ada
    //         printf("Obat yang harus diberikan:\n");
    //         int j = 0;
    //         while(obatpenyakit->obat[i][j] != NULL){
    //             printf("%d. %s\n", j+1, obatpenyakit->obat[i][j]);
    //             j++;
    //         }
    //     }
    // }
    // printf("Obat dari penyakit %s tidak ditemukan\n", pasien.riwayat_penyakit);
    return 1;
}