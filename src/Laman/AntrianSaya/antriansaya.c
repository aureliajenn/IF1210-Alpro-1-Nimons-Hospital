#include "main.h"

int lamanLihatAntrianSaya() {
    extern User *user;
    extern Map *map;
    extern Hospital rumahSakit;
    extern User *users;
    extern int jumlah_user;

    // Ambil dokter yang menangani pasien ini
    Dokter *dokter = getDoctorByIdPatient(map, user->identitas.id);
    if (dokter == NULL) {
        if(user->kondisi.sudahDiagnosis==0){
            printf("\nAnda belum terdaftar dalam antrian check-up!\n");
            printf("Silakan daftar check-up terlebih dahulu.\n");
            return 1;
        }else{
            printf("Kamu sudah di diagnosis\n");
            return 1;
        }
    }

    // Cek apakah pasien sudah berada di dalam ruangan
    if(user->kondisi.sudahDiagnosis==0){
        int posisi = getQueuePosition(dokter->queue, user->identitas.id);
        if (posisi > 0 && posisi <= map->maxPasienDalamRuangan) {
            printf("\nAnda sedang berada di dalam ruangan dokter!\n");
            return 1;
        }

        // Jika tidak di ruangan, cek di antrian diagnosis
        if (queueContains(dokter->queue, user->identitas.id)) {
            int position = getQueuePosition(dokter->queue, user->identitas.id);
            char labelRuangan[5];
            dapatkanLabelRuangan(dokter->ruangan, labelRuangan, map->cols);
            const char *dokterName = dapatkanUsername(users, jumlah_user, dokter->id, "dokter");

            printf("\nStatus antrian Anda:\n");
            printf("Jenis antrian: Diagnosis\n");
            printf("Dokter: %s\n", dokterName);
            printf("Ruangan: %s\n", labelRuangan);
            printf("Posisi antrian: %d dari %d\n", position-map->maxPasienDalamRuangan, dokter->queueLength-map->maxPasienDalamRuangan);
            return 1;
        }
        printf("Kamu belum di diagnosis\n");
        return 1;
    }

    if(user->kondisi.sudahDiagnosis==1){
    // Cek apakah pasien sudah berada di dalam ruangan
    int posisiNg = getQueuePosition(dokter->queueNg, user->identitas.id);
    if (posisiNg > 0 && posisiNg <= map->maxPasienDalamRuangan) {
        printf("\nAnda sedang berada di dalam ruangan dokter!\n");
        return 1;
    }

    // Cek di antrian pengobatan
    if (queueContains(dokter->queueNg, user->identitas.id)) {
        // Asumsikan posisi juga bisa dihitung dengan getQueuePosition
        int position = getQueuePosition(dokter->queueNg, user->identitas.id);
        char labelRuangan[5];
        dapatkanLabelRuangan(dokter->ruangan, labelRuangan, map->cols);
        const char *dokterName = dapatkanUsername(users, jumlah_user, dokter->id, "dokter");

        printf("\nStatus antrian Anda:\n");
        printf("Jenis antrian: Pengobatan\n");
        printf("Dokter: %s\n", dokterName);
        printf("Ruangan: %s\n", labelRuangan);
        printf("Posisi antrian: %d dari %d\n", position-map->maxPasienDalamRuangan, dokter->queueLengthNg-map->maxPasienDalamRuangan);
        return 1;
        }
    printf("Kamu sudah di diagnosis\n");
    return 1;
    }

    // Pasien tidak ditemukan di antrian manapun
    printf("Anda belum terdaftar dalam antrian check-up!\n");
    printf("Silakan daftar check-up terlebih dahulu.\n");
    return 1;
}