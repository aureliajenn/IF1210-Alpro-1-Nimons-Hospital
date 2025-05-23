#include <stdio.h>
#include <string.h>
#include "../daftarcheckup/daftar_checkup.h"

void validateData(char *head, char *desc, int data) {
	printf("%s (%s): ", head, desc);
	scanf("%d", data);
	while (data < 0) {
		for (int i = 0; i < strlen(head); i++) {
			if (i > 0) {
				printf("%c", toLowerCase(head[i]));
			} else {
				printf("%c", head[i]);
			}
		}
		printf(" harus berupa angka positif!\n");
		scanf("%d", data);
	}
}

void validatefData(char *head, char *desc, float data) {
	printf("%s (%s): ", head, desc);
	scanf("%d", data);
	while (data < 0) {
		for (int i = 0; i < strlen(head); i++) {
			if (i > 0) {
				printf("%c", toLowerCase(head[i]));
			} else {
				printf("%c", head[i]);
			}
		}
		printf(" harus berupa angka positif!\n");
		scanf("%d", data);
	}
}

void validate2Data(char *head, char *desc, int *data1, int *data2) {
	printf("%s (%s): ", head, desc);
	scanf("%d %d", data1, data2);
	while (*data1 < 0 || *data2 < 0) {
		for (int i = 0; i < strlen(head); i++) {
			if (i > 0) {
				printf("%c", toLowerCase(head[i]));
			} else {
				printf("%c", head[i]);
			}
		}
		printf(" harus berupa angka positif!\n");
		scanf("%d %d", data1, data2);
	}
}

Map* getavailableDokter(Map* map) {
    if (map == NULL) return NULL;
    
    Map* availableDokter = malloc(sizeof(Map));
    if (availableDokter == NULL) return NULL;
    
    availableDokter->capacity = map->capacity;
    availableDokter->size = 0;
    availableDokter->maxPasienDalamRuangan = map->maxPasienDalamRuangan;
    availableDokter->maxAntrianLuar = map->maxAntrianLuar;
    availableDokter->rows = map->rows;
    availableDokter->cols = map->cols;
    
    availableDokter->dokter = malloc(sizeof(Dokter*) * map->capacity);
    if (availableDokter->dokter == NULL) {
        free(availableDokter);
        return NULL;
    }
    
    for (int i = 0; i < map->size; i++) {
        if (map->dokter[i] == NULL) continue;
        
        int should_add = 0;
        if (map->dokter[i]->jumlahPasienDalamRuangan <= map->maxPasienDalamRuangan) {
            should_add = 1;
        } else if (map->dokter[i]->jumlahPasienLuarRuangan <= map->maxAntrianLuar) {
            should_add = 1;
        }
        
        if (should_add) {
            availableDokter->dokter[availableDokter->size] = map->dokter[i];
            availableDokter->size++;
        }
    }
    
    return availableDokter;
}

int isSudahNgantri(Map *map, User *user) {
    for (int i = 0; i < map->size; i++) {
        if (map->dokter[i]->queue != NULL) {
            QueueNode *current = map->dokter[i]->queue->front;

            while (current != NULL) {
                
                if (current->patient.id == user->identitas.id) {
                    printf("Anda sudah terdaftar dalam antrian!\n");
                    return 1; 
                }
                current = current->next; 
            }
        }
    }

    return 0; 
}



void daftar_checkup() {
    extern Map *map;
    extern int jumlah_user;
    extern User *users;
    extern User *user;

  if(isSudahNgantri(map, user)==1) {
        return;
    }
  
    float suhu, oksigen, berat, tinggi;
    int sistol, diastol, bpm, gula, kolestrol, ldl, trombosit;

    printf("Silakan masukkan data check-up Anda:\n");

    validatefData("Suhu Tubuh", "Celcius", suhu);
	validate2Data("Tekanan Darah", "sistol/diastol, contoh 120 80", sistol, diastol);
	validateData("Detak Jantung", "bpm", bpm);
	validatefData("Saturasi Oksigen", "%%", oksigen);
	validateData("Kadar Gula Darah", "mg/dL", gula);
	validatefData("Berat Badan", "kg", berat);
	validatefData("Tinggi Badan", "cm", tinggi);
	validateData("Kadar Kolestrol", "mg/dL", kolestrol);
	validateData("Kadar Kolestrol LDL", "mg/dL", ldl);
	validateData("Trombosit", "ribu/mikroL", trombosit);

    printf("\nBerikut adalah daftar dokter yang tersedia:\n");

    Map* dokter_list = getavailableDokter(map);
    for (int i = 0; i < dokter_list->size; i++) {
        int dokterId = dokter_list->dokter[i]->id;
        
        char *dokterName = "DOKTER TIDAK DITEMUKAN";
        for (int j = 0; j < jumlah_user; j++) {
            if (strcmpIgnoreCase(users[j].identitas.role, "dokter") == 0 && users[j].identitas.id == dokterId) {
                dokterName = users[j].identitas.username; 
                break;
            }
        }

        char labelRuangan[5];
        dapatkanLabelRuangan(dokter_list->dokter[i]->ruangan, labelRuangan, map->cols);

        printf("%d. dr. %s - Ruangan %s (Antrian: %d orang)\n", i+1, dokterName, labelRuangan, dokter_list->dokter[i]->jumlahPasienLuarRuangan);
    }
   

    int pilihan;
    do {
        printf("Pilih dokter (1-%d): ", dokter_list->size);
        scanf("%d", &pilihan);
    } while (pilihan < 1 || pilihan > dokter_list->size);

    Pasien pasien;
    pasien.id = user->identitas.id;
    strncpy(pasien.nama, user->identitas.username, sizeof(pasien.nama) - 1);
    pasien.nama[sizeof(pasien.nama) - 1] = '\0';
    
    
    pasien.suhu_tubuh = suhu;
    pasien.tekanan_darah_sistolik = sistol;
    pasien.tekanan_darah_diastolik = diastol;
    pasien.detak_jantung = bpm;
    pasien.saturasi_oksigen = oksigen;
    pasien.kadar_gula_darah = gula;
    pasien.berat_badan = berat;
    pasien.tinggi_badan = tinggi;
    pasien.kadar_kolesterol = kolestrol;
    pasien.kadar_kolesterol_ldl = ldl;
    pasien.trombosit = trombosit;

    user->kondisi.suhu_tubuh = suhu;
    user->kondisi.tekanan_darah_sistolik = sistol;
    user->kondisi.tekanan_darah_diastolik = diastol;
    user->kondisi.detak_jantung = bpm;
    user->kondisi.saturasi_oksigen = oksigen;
    user->kondisi.kadar_gula_darah = gula;
    user->kondisi.berat_badan = berat;
    user->kondisi.tinggi_badan = tinggi;
    user->kondisi.kadar_kolesterol = kolestrol;
    user->kondisi.kadar_kolesterol_ldl = ldl;
    user->kondisi.trombosit = trombosit;

    users[user->identitas.id - 1].kondisi.suhu_tubuh = suhu;
    users[user->identitas.id - 1].kondisi.tekanan_darah_sistolik = sistol;
    users[user->identitas.id - 1].kondisi.tekanan_darah_diastolik = diastol;
    users[user->identitas.id - 1].kondisi.detak_jantung = bpm;
    users[user->identitas.id - 1].kondisi.saturasi_oksigen = oksigen;
    users[user->identitas.id - 1].kondisi.kadar_gula_darah = gula;
    users[user->identitas.id - 1].kondisi.berat_badan = berat;
    users[user->identitas.id - 1].kondisi.tinggi_badan = tinggi;
    users[user->identitas.id - 1].kondisi.kadar_kolesterol = kolestrol;
    users[user->identitas.id - 1].kondisi.kadar_kolesterol_ldl = ldl;
    users[user->identitas.id - 1].kondisi.trombosit = trombosit;


    map->dokter[pilihan - 1]->queueLength++;
    if(map->dokter[pilihan - 1]->jumlahPasienDalamRuangan <= map->maxPasienDalamRuangan) {
        map->dokter[pilihan - 1]->jumlahPasienDalamRuangan++;
    } else {
        map->dokter[pilihan - 1]->jumlahPasienLuarRuangan++;
    }

    enqueue(map->dokter[pilihan - 1]->queue, pasien);

    char *dokterName = "DOKTER TIDAK DITEMUKAN";
    for (int j = 0; j < jumlah_user; j++) {
        if (strcmpIgnoreCase(users[j].identitas.role, "dokter") == 0 && users[j].identitas.id == dokter_list->dokter[pilihan - 1]->id) {
            dokterName = users[j].identitas.username; 
            break;
        }
    }

    char labelRuangan[5];
    dapatkanLabelRuangan(dokter_list->dokter[pilihan -1]->ruangan, labelRuangan, map->cols);

    
    printf("\nPendaftaran check-up berhasil!\n");
    printf("Anda terdaftar pada antrian dokter: %s, di ruangan: %s\n", dokterName, labelRuangan);
   
    printf("Posisi antrian Anda: %d\n", map->dokter[pilihan - 1]->queue->size);
}