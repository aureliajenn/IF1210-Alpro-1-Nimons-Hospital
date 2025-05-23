#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // Untuk cek folder
#include "../Model/model.h"
#include "../DataParser/dataParser.h"
#include "../Utils/map.h"
#include "../Laman/Denah/denah.h"

// Deklarasi global dari main.c
extern User *users;
extern Penyakit *penyakits;
extern int jumlah_user;
extern int jumlah_penyakit;




void load(const char *folder_name) {
    char userpath[256], penyakitpath[256];

    sprintf(userpath, "data/%s/user.csv", folder_name);
    sprintf(penyakitpath, "data/%s/penyakit.csv", folder_name);

    // Cek apakah folder ada
    char folderpath[256];
    sprintf(folderpath, "data/%s", folder_name);

    struct stat st;
    if (stat(folderpath, &st) != 0 || !S_ISDIR(st.st_mode)) {
        printf("Folder \"%s\" tidak ditemukan di dalam folder data/.\n", folder_name);
        exit(1);
    }
    // Reset jumlah
    jumlah_user = 0;
    jumlah_penyakit = 0;

    ParseTarget pt = {users, &jumlah_user};
    ParsePenyakit pp = {penyakits, &jumlah_penyakit};

    // Load file CSV ke array
    CSVtoArr(userpath, handleUserRow, &pt);
    CSVtoArr(penyakitpath, handlePenyakitRow, &pp);

    // Realloc
    User *temp_users = realloc(users, jumlah_user * sizeof(User));
    if (temp_users == NULL) {
        perror("Gagal realloc users");
        free(users);
        exit(1);
    }
    users = temp_users;

    printf("Loading...\n");
}

User *getUserById(int id) {
    for (int i = 0; i < jumlah_user; i++) {
        if (users[i].identitas.id == id) {
            return &users[i];
        }
    }
    return NULL;
}


Map *loadConfig(const char *configPath) {
    Map *map = NULL;
    FILE *file = fopen(configPath, "r");
    if (!file) {
        perror("Gagal membuka file config.txt");
        return;
    }

    char baris[MAX_LINE_LEN];
    int hitungBaris = 0;
    int barisD;
    int kolomD;

     while (fgets(baris, MAX_LINE_LENGTH, file)) {
        baris[strcspn(baris, "\n")] = 0; 
        
        hitungBaris++;
        
        if (hitungBaris == 1) {
            char rowsStr[10], colsStr[10];
            int i = 0;
            
            while (baris[i] >= '0' && baris[i] <= '9') {
                rowsStr[i] = baris[i];
                i++;
            }
            rowsStr[i] = '\0';  
            barisD = convertStringToInt(rowsStr);
            
            i++;  
            int j = 0;
            while (baris[i] >= '0' && baris[i] <= '9') {
                colsStr[j] = baris[i];
                i++;
                j++;
            }
            colsStr[j] = '\0';  
            kolomD = convertStringToInt(colsStr);
            map = createMap(barisD * kolomD);
            map->rows = barisD;
            map->cols = kolomD;
        } else if (hitungBaris == 2) {
            char maxPatientsInRoomStr[10]; char maxPatiensOutRoomStr[10];
            int i = 0;
            
            while (baris[i] >= '0' && baris[i] <= '9') {
                maxPatientsInRoomStr[i] = baris[i];
                i++;
            }
            maxPatientsInRoomStr[i] = '\0';
            int maxPatientsInRoom = convertStringToInt(maxPatientsInRoomStr);
            map->maxPasienDalamRuangan = maxPatientsInRoom;

            i++;  
            int j = 0;
            while (baris[i] >= '0' && baris[i] <= '9') {
                maxPatiensOutRoomStr[j] = baris[i];
                i++;
                j++;
            }
            maxPatiensOutRoomStr[j] = '\0'; 
            int maxPatientsOutRoom = convertStringToInt(maxPatiensOutRoomStr);
            map->maxAntrianLuar = maxPatientsOutRoom;
        } else if (hitungBaris <= 8) {
            int nilai[MAX_PATIENTS + 1]; 
            int hitungNilai = 0;
            int i = 0;

            while (baris[i] != '\0') {
                if (baris[i] >= '0' && baris[i] <= '9') {
                    char temp[10];
                    int j = 0;
                    while (baris[i] >= '0' && baris[i] <= '9') {
                        temp[j] = baris[i];
                        j++;
                        i++;
                    }
                    temp[j] = '\0';  
                    nilai[hitungNilai++] = convertStringToInt(temp);
                } else {
                    i++;
                }
            }
            
            if (hitungNilai >= 1) {
                Dokter *dokter = malloc(sizeof(Dokter));
                if (dokter == NULL) {
                    perror("Gagal mengalokasikan memori untuk dokter");
                    fclose(file);
                    return;
                }

                dokter->id = nilai[0];
                dokter->ruangan = hitungBaris - 3; 

                int jumlahPasienDalamRuangan = 0;
                int jumlahPasienLuarRuangan = 0;
                int queueLength = 0;
                dokter->queue = createQueue(); 


                for (int i = 1; i < hitungNilai; i++) {
                    if (nilai[i] > 0) { 
                        if (jumlahPasienDalamRuangan < map->maxPasienDalamRuangan) {
                            jumlahPasienDalamRuangan++; 
                        } else if (jumlahPasienLuarRuangan < map->maxAntrianLuar) {
                            jumlahPasienLuarRuangan++;  
                        }
                        queueLength++;  
                        User *pasien = getUserById(nilai[i]);
                        Pasien pasienData;
                        pasienData.id = pasien->identitas.id;
                        strcpy(pasienData.nama, pasien->identitas.username);
                        pasienData.suhu_tubuh = pasien->kondisi.suhu_tubuh;
                        pasienData.tekanan_darah_sistolik = pasien->kondisi.tekanan_darah_sistolik;
                        pasienData.tekanan_darah_diastolik = pasien->kondisi.tekanan_darah_diastolik;
                        pasienData.detak_jantung = pasien->kondisi.detak_jantung;
                        pasienData.saturasi_oksigen = pasien->kondisi.saturasi_oksigen;
                        pasienData.kadar_gula_darah = pasien->kondisi.kadar_gula_darah;
                        pasienData.berat_badan = pasien->kondisi.berat_badan;
                        pasienData.tinggi_badan = pasien->kondisi.tinggi_badan;
                        pasienData.kadar_kolesterol = pasien->kondisi.kadar_kolesterol;
                        pasienData.kadar_kolesterol_ldl = pasien->kondisi.kadar_kolesterol_ldl;
                        pasienData.trombosit = pasien->kondisi.trombosit;

                        enqueue(dokter->queue, pasienData);
                    }
                }

                dokter->jumlahPasienDalamRuangan = jumlahPasienDalamRuangan;
                dokter->jumlahPasienLuarRuangan = jumlahPasienLuarRuangan;
                dokter->queueLength = queueLength;


                if (dokter->id != 0) {
                    insertDoctor(map, dokter);
                }
            }
        } else {
            int nilai[MAX_PATIENTS];
            int hitungNilai = 0;
            int i = 0;
            
            while (baris[i] != '\0') {
                if (baris[i] >= '0' && baris[i] <= '9') {
                    char temp[10];
                    int j = 0;
                    while (baris[i] >= '0' && baris[i] <= '9') {
                        temp[j] = baris[i];
                        j++;
                        i++;
                    }
                    temp[j] = '\0'; 
                    nilai[hitungNilai++] = convertStringToInt(temp);
                } else {
                    i++;
                }
            }
            
          
        }
    }


    fclose(file);

    return map;
}
