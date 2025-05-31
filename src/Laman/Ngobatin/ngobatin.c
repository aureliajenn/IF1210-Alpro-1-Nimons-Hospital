// #include "main.h"

// int lamanNgobatin(){
//     extern User *user;
//     extern ObatPenyakit *obat_penyakits;
//     extern Penyakit *penyakits;
//     extern Penyakit *obats;
//     extern int jumlah_obat_penyakit;
//     extern int jumlah_penyakit;
//     extern int jumlah_obat;
//     extern Map *map;

//     if (user == NULL || user->identitas.role == NULL)
//     {
//         printf("Anda belum login!\n");
//         return 0;
//     }

//     if (strcmpIgnoreCase(user->identitas.role, "dokter") != 0)
//     {
//         printf("Hanya dokter yang dapat mengakses laman ini!\n");
//         return 0;
//     }

//     if (obat_penyakits == NULL || jumlah_obat_penyakit == 0)
//     {
//         printf("Data obat-penyakit tidak ditemukan!\n");
//         return 0;
//     }

//     Dokter *dokter = getDoctor(map, user->identitas.id);
//     if (dokter == NULL)
//     {
//         printf("Dokter tidak ditemukan!\n");
//         return 0;
//     }

//     Pasien pasien = dokter->queue->front->patient;
//     printf("Dokter sedang mengobati pasien %s.\n", pasien.nama);
//     printf("[Auto-Prescription-2.0] Mengobati...\n");

//     if (pasien.riwayat_penyakit == NULL) {
//         printf("Pasien %s tidak memiliki riwayat penyakit.\n", pasien.nama);
//         return 0;
//     }
//     for (int i = 0; i < jumlah_penyakit; i++){
//         if (strcmp(pasien.riwayat_penyakit, penyakits[i].nama) == 0){
//             printf("Obat yang harus diberikan:\n");
//             int urutan = 1;
//             int found = 1;
//             while (found){
//                 found = 0;
//                 for (int j = 0; j < jumlah_obat_penyakit; j++){
//                     if (penyakits[i].id == obat_penyakits[j].penyakit_id && urutan == obat_penyakits[i].urutan_minum){
//                         found = 1;
//                         char nama_obat[MAX_LINE_LENGTH];
//                         for (int k = 0; k < jumlah_obat; k++){
//                             if (obat_penyakits[i].obat_id == obats[k].id){
//                             strcpy(nama_obat, obats[k].nama);
//                             break;
//                             }
//                         }
//                         printf("%d. %s\n", urutan, nama_obat);
//                         urutan++;
//                         break;
//                     }
//                 }
//             }
//             return 1;
//         }
//     }
//     printf("Obat dari penyakit %s tidak ditemukan\n", pasien.riwayat_penyakit);
//     return 0;
// }