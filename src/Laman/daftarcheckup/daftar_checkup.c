#include <stdio.h>
#include <string.h>
#include "daftar_checkup.h"

int pasien_terdaftar(const char* pasien, MapPasien* map, int jumlah_map) {
    for (int i = 0; i < jumlah_map; i++) {
        if (strcmp(map[i].nama_pasien, pasien) == 0) {
            return 1;
        }
    }
    return 0;
}

void daftar_checkup(const char* pasien, Dokter* dokter_list, int jumlah_dokter, MapPasien* map, int* jumlah_map) {
    if (pasien_terdaftar(pasien, map, *jumlah_map)) {
        printf("Anda sudah terdaftar dalam antrian check-up!\n");
        printf("Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.\n");
        return;
    }

    float suhu, oksigen, berat, tinggi;
    int sistol, diastol, bpm, gula, kolestrol, ldl, trombosit;

    printf("Silakan masukkan data check-up Anda:\n");

    printf("Suhu Tubuh (Celcius): ");
    scanf("%f", &suhu);
    if (suhu <= 0) { printf("Suhu tubuh harus berupa angka positif!\n"); return; }

    printf("Tekanan Darah (Sistol Diastol): ");
    scanf("%d %d", &sistol, &diastol);
    if (sistol <= 0 || diastol <= 0) { printf("Tekanan darah harus berupa angka positif!\n"); return; }

    printf("Detak Jantung (bpm): ");
    scanf("%d", &bpm);

    printf("Saturasi Oksigen (%%): ");
    scanf("%f", &oksigen);

    printf("Kadar Gula Darah (mg/dL): ");
    scanf("%d", &gula);

    printf("Berat Badan (kg): ");
    scanf("%f", &berat);

    printf("Tinggi Badan (cm): ");
    scanf("%f", &tinggi);

    printf("Kadar Kolestrol (mg/dL): ");
    scanf("%d", &kolestrol);

    printf("Kadar Kolestrol LDL (mg/dL): ");
    scanf("%d", &ldl);

    printf("Trombosit (ribu/uL): ");
    scanf("%d", &trombosit);

    printf("\nBerikut adalah daftar dokter yang tersedia:\n");
    for (int i = 0; i < jumlah_dokter; i++) {
        printf("%d. %s - Ruangan %s (Antrian: %d pasien)\n",
            i + 1,
            dokter_list[i].nama_dokter,
            dokter_list[i].ruangan,
            LENGTH(&dokter_list[i].queue)
        );
    }

    int pilihan;
    do {
        printf("Pilih dokter (1-%d): ", jumlah_dokter);
        scanf("%d", &pilihan);
    } while (pilihan < 1 || pilihan > jumlah_dokter);

    int idx = pilihan - 1;

    enqueue(&dokter_list[idx].queue, pasien);
    strcpy(map[*jumlah_map].nama_pasien, pasien);
    strcpy(map[*jumlah_map].nama_dokter, dokter_list[idx].nama_dokter);
    (*jumlah_map)++;

    printf("\nPendaftaran check-up berhasil!\n");
    printf("Anda terdaftar pada antrian %s di ruangan %s.\n",
        dokter_list[idx].nama_dokter,
        dokter_list[idx].ruangan);
    printf("Posisi antrian Anda: %d\n", LENGTH(&dokter_list[idx].queue));
}