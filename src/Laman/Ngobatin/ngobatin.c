#include "main.h"

int lamanNgobatin() {
    extern User *user;
    extern ObatPenyakit *obat_penyakits;
    extern Penyakit *penyakits;
    extern Obat *obats;
    extern int jumlah_obat_penyakit;
    extern int jumlah_penyakit;
    extern int jumlah_obat;
    extern Map *map;

    if (user == NULL || user->identitas.role == NULL) {
        printf("Anda belum login!\n");
        return 0;
    }

    if (strcmpIgnoreCase(user->identitas.role, "dokter") != 0) {
        printf("Hanya dokter yang dapat mengakses laman ini!\n");
        return 0;
    }

    if (obat_penyakits == NULL || jumlah_obat_penyakit == 0) {
        printf("Data obat-penyakit tidak ditemukan!\n");
        return 0;
    }
    
    Dokter *dokter = getDoctor(map, user->identitas.id);
    if (dokter == NULL || dokter->queueNg == NULL || dokter->queueNg->front == NULL) {
        printf("Dokter tidak memiliki pasien dalam antrian!\n");
        return 0;
    }

    User *pasien = getUserById(dokter->queueNg->front->patient->identitas.id);
    if (pasien== NULL) {
        printf("Data pasien tidak ditemukan!\n");
        return 0;
    }

    printf("Dokter sedang mengobati pasien %s!\n", pasien->identitas.username);

    // Kasus: pasien belum diagnosis
    if (pasien->kondisi.sudahDiagnosis == 0) {
        printf("Pasien tidak memiliki penyakit!\n");
        printf("Pasien belum di diagnosis!\n");
        return 0; // tidak lanjut ke pasien berikutnya
    }

    // Kasus: pasien sudah pernah diobati
    if (pasien->kondisi.sudahDiobati == 1) {
        printf("Pasien %s sudah pernah diobati!\n", pasien->identitas.username);
        dequeue(dokter->queueNg); dokter->queueLengthNg--;// lewati pasien ini
        return 0;
    }

    // Mulai proses pengobatan
    printf("Pasien memiliki penyakit %s\n", pasien->kondisi.riwayat_penyakit);
    printf("Obat yang harus diberikan:\n");

    for (int i = 0; i < jumlah_penyakit; i++) {
        if (strcasecmp(pasien->kondisi.riwayat_penyakit, penyakits[i].nama) == 0) {
            int urutan = 1;
            int found = 1;
            while (found) {
                found = 0;
                for (int j = 0; j < jumlah_obat_penyakit; j++) {
                    if (penyakits[i].id == obat_penyakits[j].penyakit_id &&
                        urutan == obat_penyakits[j].urutan_minum) {
                        found = 1;
                        for (int k = 0; k < jumlah_obat; k++) {
                            if (obat_penyakits[j].obat_id == obats[k].id) {
                                printf("%d. %s\n", urutan, obats[k].nama);
                                tambahObatInventory(pasien->identitas.id, obats[k]);
                                break;
                            }
                        }   
                        urutan++;
                        break;
                    }
                }
            }

            // Set status pasien sudah diobati
            pasien->kondisi.sudahDiobati = 1;

            // Keluarkan pasien dari antrian
            dequeue(dokter->queueNg);dokter->queueLengthNg--;
            return 1;
        }
    }

    printf("Obat dari penyakit %s tidak ditemukan.\n", pasien->kondisi.riwayat_penyakit);
    dequeue(dokter->queueNg); // tetap keluarkan pasien agar tidak stuck
    dokter->queueLengthNg--;
    return 0;
}
