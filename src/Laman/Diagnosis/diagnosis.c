#include "main.h"

void printQueuePositions(Queue *q) {
    if (q == NULL || q->front == NULL) {
        printf("Queue is empty or uninitialized!\n");
        return;
    }

    QueueNode *current = q->front;
    int position = 1; 

    while (current != NULL) {
        printf("%d. Nama: %s (Antrian ke-%d)\n", position, current->patient.identitas.username, position);
        current = current->next;
        position++;
    }
}

int lamanDiagnosis()
{
    extern User *user;
    extern Penyakit *penyakits;
    extern int jumlah_penyakit;
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

    if (penyakits == NULL || jumlah_penyakit == 0)
    {
        printf("Data penyakit tidak ditemukan!\n");
        return 0;
    }

    printf("Pilih pasien yang ingin didiagnosis:\n");
    Dokter *dokter = getDoctor(map, user->identitas.id);
    if (dokter == NULL)
    {
        printf("Dokter tidak ditemukan!\n");
        return 0;
    }

    printQueuePositions(dokter->queue);
    int selectPatient;
    printf("Pilih pasien (1-%d):\n\n", dokter->queue->size);
    selectPatient = getValidIntInput(1, dokter->queue->size, ">>> Pilihan: ");

    QueueNode *current = dokter->queue->front;
    for (int i = 1; i < selectPatient; i++)
    {
        current = current->next;
    }

    User pasien = current->patient;
    printf("Diagnosa untuk pasien %s:\n", pasien.identitas.username);
    printf("[AUTO DIAGNOSE 2.0] Mendiagnosis...\n");
    printf("Hasil diagnosa:\n\n");

    int found = 0;

    for (int i = 0; i < jumlah_penyakit; i++)
    {
        if(pasien.kondisi.suhu_tubuh >= penyakits[i].suhu_tubuh_min && pasien.kondisi.suhu_tubuh <= penyakits[i].suhu_tubuh_max &&
           pasien.kondisi.tekanan_darah_sistolik >= penyakits[i].tekanan_darah_sistolik_min && pasien.kondisi.tekanan_darah_sistolik <= penyakits[i].tekanan_darah_sistolik_max &&
           pasien.kondisi.tekanan_darah_diastolik >= penyakits[i].tekanan_darah_diastolik_min && pasien.kondisi.tekanan_darah_diastolik <= penyakits[i].tekanan_darah_diastolik_max &&
           pasien.kondisi.detak_jantung >= penyakits[i].detak_jantung_min && pasien.kondisi.detak_jantung <= penyakits[i].detak_jantung_max &&
           pasien.kondisi.saturasi_oksigen >= penyakits[i].saturasi_oksigen_min && pasien.kondisi.saturasi_oksigen <= penyakits[i].saturasi_oksigen_max &&
           pasien.kondisi.kadar_gula_darah >= penyakits[i].kadar_gula_darah_min && pasien.kondisi.kadar_gula_darah <= penyakits[i].kadar_gula_darah_max &&
           pasien.kondisi.berat_badan >= penyakits[i].berat_badan_min && pasien.kondisi.berat_badan <= penyakits[i].berat_badan_max &&
           pasien.kondisi.tinggi_badan >= penyakits[i].tinggi_badan_min && pasien.kondisi.tinggi_badan <= penyakits[i].tinggi_badan_max &&
           pasien.kondisi.kadar_kolesterol >= penyakits[i].kadar_kolesterol_min && pasien.kondisi.kadar_kolesterol <= penyakits[i].kadar_kolesterol_max &&
           
           pasien.kondisi.trombosit >= penyakits[i].trombosit_min && pasien.kondisi.trombosit <= penyakits[i].trombosit_max)
        {
            printf("%s terdiagnosa penyakit: %s\n\n", pasien.identitas.username, penyakits[i].nama);
            found =1;
            dequeue(dokter->queue);
            dokter->queueLength--;
            if (dokter->jumlahPasienDalamRuangan > 0)
            {
                dokter->jumlahPasienDalamRuangan--;
            }
            else
            {
                dokter->jumlahPasienLuarRuangan--;
            }
            printf("Pasien %s telah keluar dari antrian.\n", pasien.identitas.username);
            break;
        }
    }

    if (!found)
    {
        printf("Tidak ada penyakit yang terdiagnosa untuk pasien %s.\n", pasien.identitas.username);
    }



    return 1;
}