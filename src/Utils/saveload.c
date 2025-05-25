#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saveload.h"
#include "../Auth/auth.h"
#include "../DataParser/dataParser.h"
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
extern Hospital *rumahSakit;

void make_folder(const char* path) {
    char command[256];
    sprintf(command, "mkdir -p %s", path);
    system(command);
}

void save(const char folder_name[]) {
    char base_path[] = "data";
    char full_path[MAX_LINE_LEN];
    sprintf(full_path, "%s/%s", base_path, folder_name);

    // Bikin folder kalau belum ada
    char test_file[MAX_LINE_LEN];
    sprintf(test_file, "%s/user.csv", full_path);
    FILE* test = fopen(test_file, "r");

    if (test == NULL) {
        printf("Membuat folder %s...\n", full_path);
        make_folder(full_path);
        printf("Saving...\n");
    } else {
        fclose(test);
        printf("Saving...\n");
    }

    // Menyimpan data user
    char user_file[MAX_LINE_LEN];
    sprintf(user_file, "%s/user.csv", full_path);
    FILE* userfile = fopen(user_file, "w");
    if (userfile != NULL) {
        fprintf(userfile, "id;username;password;role;riwayat_penyakit;suhu_tubuh;tekanan_darah_sistolik;tekanan_darah_diastolik;detak_jantung;saturasi_oksigen;kadar_gula_darah;berat_badan;tinggi_badan;kadar_kolesterol;kadar_kolesterol_ldl;trombosit\n");
        for (int i = 0; i < jumlah_user; i++) {
            fprintf(userfile, "%d;%s;%s;%s;%s;%.2f;%d;%d;%d;%.2f;%d;%.2f;%d;%d;%d;%d\n",
                i + 1,
                users[i].identitas.username,
                users[i].identitas.password,
                users[i].identitas.role,
                users[i].kondisi.riwayat_penyakit,
                users[i].kondisi.suhu_tubuh,
                users[i].kondisi.tekanan_darah_sistolik,
                users[i].kondisi.tekanan_darah_diastolik,
                users[i].kondisi.detak_jantung,
                users[i].kondisi.saturasi_oksigen,
                users[i].kondisi.kadar_gula_darah,
                users[i].kondisi.berat_badan,
                users[i].kondisi.tinggi_badan,
                users[i].kondisi.kadar_kolesterol,
                users[i].kondisi.kadar_kolesterol_ldl,
                users[i].kondisi.trombosit
            );
        }
        fclose(userfile);
        printf("Berhasil menyimpan data user di folder %s!\n", full_path);
    } else {
        printf("Gagal menyimpan file user.csv di %s\n", full_path);
    }

    // Menyimpan data penyakit
    char penyakit_file[MAX_LINE_LEN];
    sprintf(penyakit_file, "%s/penyakit.csv", full_path);
    FILE* penyakitfile = fopen(penyakit_file, "w");
    if (penyakitfile != NULL) {
        fprintf(penyakitfile, "id;nama_penyakit;suhu_tubuh_min;suhu_tubuh_max;tekanan_darah_sistolik_min;tekanan_darah_sistolik_max;tekanan_darah_diastolik_min;tekanan_darah_diastolik_max;detak_jantung_min;detak_jantung_max;saturasi_oksigen_min;saturasi_oksigen_max;kadar_gula_darah_min;kadar_gula_darah_max;berat_badan_min;berat_badan_max;tinggi_badan_min;tinggi_badan_max;kadar_kolesterol_min;kadar_kolesterol_max;trombosit_min;trombosit_max\n");
        for (int i = 0; i < jumlah_penyakit; i++) {
            fprintf(penyakitfile, "%d;%s;%.1f;%.1f;%d;%d;%d;%d;%d;%d;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%d;%d;%d;%d;%d;%d\n",
                penyakits[i].id,
                penyakits[i].nama,
                penyakits[i].suhu_tubuh_min,
                penyakits[i].suhu_tubuh_max,
                penyakits[i].tekanan_darah_sistolik_min,
                penyakits[i].tekanan_darah_sistolik_max,
                penyakits[i].tekanan_darah_diastolik_min,
                penyakits[i].tekanan_darah_diastolik_max,
                penyakits[i].detak_jantung_min,
                penyakits[i].detak_jantung_max,
                penyakits[i].saturasi_oksigen_min,
                penyakits[i].saturasi_oksigen_max,
                penyakits[i].kadar_gula_darah_min,
                penyakits[i].kadar_gula_darah_max,
                penyakits[i].berat_badan_min,
                penyakits[i].berat_badan_max,
                penyakits[i].tinggi_badan_min,
                penyakits[i].tinggi_badan_max,
                penyakits[i].kadar_kolesterol_min,
                penyakits[i].kadar_kolesterol_max,
                penyakits[i].trombosit_min,
                penyakits[i].trombosit_max
            );
        }
        fclose(penyakitfile);
        printf("Berhasil menyimpan data penyakit di folder %s!\n", full_path);
    } else {
        printf("Gagal menyimpan file penyakit.csv di %s\n", full_path);
    }

    // Menyimpan file config.txt
    char config_file[MAX_LINE_LEN];
    sprintf(config_file, "%s/config.txt", full_path);
    FILE* configfile = fopen(config_file, "w");
    if (configfile != NULL) {
        // Menyimpan informasi ukuran rumah sakit dan antrian
        fprintf(configfile, "%d %d\n", rumahSakit->rows, rumahSakit->cols);  // Ukuran denah
        fprintf(configfile, "%d %d\n", rumahSakit->maxPatientsPerRoom, rumahSakit->maxQueue);  // Batas pasien di ruangan dan antrian luar
        
        // Menyimpan status ruangan
        for (int i = 0; i < rumahSakit->roomCount; i++) {
            fprintf(configfile, "%d", rumahSakit->rooms[i].doctorId);
            for (int j = 0; j < rumahSakit->rooms[i].patientCount; j++) {
                fprintf(configfile, " %d", rumahSakit->rooms[i].patients[j]);
            }
            for (int j = 0; j < rumahSakit->rooms[i].queueCount; j++) {
                fprintf(configfile, " %d", rumahSakit->rooms[i].queue[j]);
            }
            fprintf(configfile, "\n");
        }
        
        // Menyimpan informasi obat
        fprintf(configfile, "%d\n", rumahSakit->medicineCount);
        for (int i = 0; i < rumahSakit->medicineCount; i++) {
            fprintf(configfile, "%d %d\n", rumahSakit->medicines[i].patientId, rumahSakit->medicines[i].medicineCount);
        }
        
        fclose(configfile);
        printf("Berhasil menyimpan data konfigurasi di folder %s!\n", full_path);
    } else {
        printf("Gagal menyimpan file config.txt di %s\n", full_path);
    }
}


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
    extern Map *map;
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
