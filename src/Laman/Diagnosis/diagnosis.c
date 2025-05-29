#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "diagnosis.h"

void printQueuePositions(Queue *q) {
    if (q == NULL || q->front == NULL) {
        printf("Queue is empty or uninitialized!\n");
        return;
    }

    QueueNode *current = q->front;
    int position = 1; 

    while (current != NULL) {
        printf("%d. Nama: %s (Antrian ke-%d)\n", position, current->patient.nama, position);
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

    Pasien pasien = current->patient;
    printf("Diagnosa untuk pasien %s:\n", pasien.nama);
    printf("[AUTO DIAGNOSE 2.0] Mendiagnosis...\n");
    printf("Hasil diagnosa:\n\n");

    int found = 0;

    for (int i = 0; i < jumlah_penyakit; i++)
    {
        if(pasien.suhu_tubuh >= penyakits[i].suhu_tubuh_min && pasien.suhu_tubuh <= penyakits[i].suhu_tubuh_max &&
           pasien.tekanan_darah_sistolik >= penyakits[i].tekanan_darah_sistolik_min && pasien.tekanan_darah_sistolik <= penyakits[i].tekanan_darah_sistolik_max &&
           pasien.tekanan_darah_diastolik >= penyakits[i].tekanan_darah_diastolik_min && pasien.tekanan_darah_diastolik <= penyakits[i].tekanan_darah_diastolik_max &&
           pasien.detak_jantung >= penyakits[i].detak_jantung_min && pasien.detak_jantung <= penyakits[i].detak_jantung_max &&
           pasien.saturasi_oksigen >= penyakits[i].saturasi_oksigen_min && pasien.saturasi_oksigen <= penyakits[i].saturasi_oksigen_max &&
           pasien.kadar_gula_darah >= penyakits[i].kadar_gula_darah_min && pasien.kadar_gula_darah <= penyakits[i].kadar_gula_darah_max &&
           pasien.berat_badan >= penyakits[i].berat_badan_min && pasien.berat_badan <= penyakits[i].berat_badan_max &&
           pasien.tinggi_badan >= penyakits[i].tinggi_badan_min && pasien.tinggi_badan <= penyakits[i].tinggi_badan_max &&
           pasien.kadar_kolesterol >= penyakits[i].kadar_kolesterol_min && pasien.kadar_kolesterol <= penyakits[i].kadar_kolesterol_max &&
           
           pasien.trombosit >= penyakits[i].trombosit_min && pasien.trombosit <= penyakits[i].trombosit_max)
        {
            printf("%s terdiagnosa penyakit: %s\n\n", pasien.nama, penyakits[i].nama);
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
            printf("Pasien %s telah keluar dari antrian.\n", pasien.nama);
            break;
        }
    }

    if (!found)
    {
        printf("Tidak ada penyakit yang terdiagnosa untuk pasien %s.\n", pasien.nama);
    }



    return 1;
}