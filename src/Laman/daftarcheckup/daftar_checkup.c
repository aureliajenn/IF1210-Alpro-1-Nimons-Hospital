#include "main.h"
#include <ctype.h>

int parse_int(const char *str, int *out) {
    int i = 0;
    int val = 0;
    int digit_found = 0;

    // Skip spasi
    while (str[i] && isspace(str[i])) i++;

    // Cek optional tanda + atau -
    int sign = 1;
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    // Parse digit satu-satu
    for (; str[i] != '\0' && str[i] != '\n'; i++) {
        if (!isdigit(str[i])) {
            return 0; // invalid char selain digit
        }
        digit_found = 1;
        val = val * 10 + (str[i] - '0');
    }

    if (!digit_found) return 0;

    *out = val * sign;
    return 1;
}

void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int is_valid_int(const char *str) {
    int i = 0;
    // Bisa ada spasi di depan
    while (isspace(str[i])) i++;

    // Boleh ada tanda minus (tapi nanti dicek > 0)
    if (str[i] == '-' || str[i] == '+') i++;

    int digit_found = 0;
    for (; str[i] != '\0' && str[i] != '\n'; i++) {
        if (!isdigit(str[i]))
            return 0;
        digit_found = 1;
    }
    return digit_found;
}

int is_valid_float(const char *str) {
    int i = 0;
    int digit_found = 0;
    int dot_found = 0;

    while (isspace(str[i])) i++;

    if (str[i] == '-' || str[i] == '+') i++;

    for (; str[i] != '\0' && str[i] != '\n'; i++) {
        if (str[i] == '.') {
            if (dot_found) return 0; // lebih dari 1 titik
            dot_found = 1;
        } else if (!isdigit(str[i])) {
            return 0;
        } else {
            digit_found = 1;
        }
    }
    return digit_found;
}

void validateData(char *head, char *desc, int *data) {
    char input[100];
    long val;
    char *endptr;

    while (1) {
        printf("%s (%s): ", head, desc);
        if (!fgets(input, sizeof(input), stdin)) {
            // Error input
            printf("Input error!\n");
            continue;
        }
        if (!is_valid_int(input)) {
            printf("%s harus berupa angka bulat positif!\n", head);
            continue;
        }
        val = strtol(input, &endptr, 10);
        if (val < 0) {
            printf("%s harus berupa angka bulat positif!\n", head);
            continue;
        }
        *data = (int)val;
        break;
    }
}

void validatefData(char *head, char *desc, float *data) {
    char input[100];
    float val;

    while (1) {
        printf("%s (%s): ", head, desc);
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Input error!\n");
            continue;
        }
        if (!is_valid_float(input)) {
            printf("%s harus berupa angka positif!\n", head);
            continue;
        }
        val = strtof(input, NULL);
        if (val < 0) {
            printf("%s harus berupa angka positif!\n", head);
            continue;
        }
        *data = val;
        break;
    }
}

void validate2Data(char *head, char *desc, int *data1, int *data2) {
    char input[100];
    long val1, val2;
    char *p1, *p2;

    while (1) {
        printf("%s (%s): ", head, desc);
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Input error!\n");
            continue;
        }

        // Split manual: cari spasi pertama
        p1 = input;
        while (*p1 && isspace(*p1)) p1++; // skip leading spaces

        p2 = p1;
        while (*p2 && !isspace(*p2)) p2++; // end of first number

        if (*p2 == '\0' || *p2 == '\n') {
            printf("%s harus berupa dua angka bulat positif dipisah spasi!\n", head);
            continue;
        }

        // ganti spasi jadi \0 buat pisah string
        *p2 = '\0';
        p2++;
        while (*p2 && isspace(*p2)) p2++; // skip spasi ke angka kedua

        // Validasi keduanya
        if (!is_valid_int(p1) || !is_valid_int(p2)) {
            printf("%s harus berupa dua angka bulat positif dipisah spasi!\n", head);
            continue;
        }

        val1 = strtol(p1, NULL, 10);
        val2 = strtol(p2, NULL, 10);

        if (val1 < 0 || val2 < 0) {
            printf("%s harus berupa dua angka bulat positif dipisah spasi!\n", head);
            continue;
        }

        *data1 = (int)val1;
        *data2 = (int)val2;
        break;
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
                
                if (current->patient.identitas.id == user->identitas.id) {
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
    extern Hospital *rumahSakit;

    if (isSudahNgantri(map, user) == 1) {
        return;
    }

    float suhu, oksigen, berat, tinggi;
    int sistol, diastol, bpm, gula, kolestrol, ldl, trombosit;

    printf("Silakan masukkan data check-up Anda:\n");
    validatefData("Suhu Tubuh", "Celcius", &suhu);
    validate2Data("Tekanan Darah", "sistol/diastol, contoh 120 80", &sistol, &diastol);
    validateData("Detak Jantung", "bpm", &bpm);
    validatefData("Saturasi Oksigen", "%%", &oksigen);
    validateData("Kadar Gula Darah", "mg/dL", &gula);
    validatefData("Berat Badan", "kg", &berat);
    validatefData("Tinggi Badan", "cm", &tinggi);
    validateData("Kadar Kolestrol", "mg/dL", &kolestrol);
    validateData("Kadar Kolestrol LDL", "mg/dL", &ldl);
    validateData("Trombosit", "ribu/mikroL", &trombosit);

    printf("\nBerikut adalah daftar dokter yang tersedia:\n");

    Map *dokter_list = getavailableDokter(map);

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

        printf("%d. dr. %s - Ruangan %s (Antrian: %d orang)\n", i + 1, dokterName, labelRuangan,
               dokter_list->dokter[i]->jumlahPasienDalamRuangan + dokter_list->dokter[i]->jumlahPasienLuarRuangan);
    }

    char line[100];
    int pilihan;

    do {
        printf("Pilih dokter (1-%d): ", dokter_list->size);

        if (!fgets(line, sizeof(line), stdin)) {
            // Input error, ulangi
            continue;
        }

        if (!parse_int(line, &pilihan)) {
            printf("Input tidak valid, harus angka!\n");
            continue;
        }

        if (pilihan < 1 || pilihan > dokter_list->size) {
            printf("Pilihan di luar rentang!\n");
            continue;
        }

        break;
    } while (1);


    int dokterIdTerpilih = dokter_list->dokter[pilihan - 1]->id;
    User *dokterValid = NULL;

    for (int j = 0; j < jumlah_user; j++) {
        if (strcmpIgnoreCase(users[j].identitas.role, "dokter") == 0 && users[j].identitas.id == dokterIdTerpilih) {
            dokterValid = &users[j];
            break;
        }
    }

    if (dokterValid == NULL) {
        printf("Dokter tidak ditemukan di sistem. Pendaftaran dibatalkan.\n");
        return;
    }

    // Isi data kondisi pasien
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

    // Update juga ke array users, dan arahkan user ke elemen yang valid
    for (int i = 0; i < jumlah_user; i++) {
        if (users[i].identitas.id == user->identitas.id) {
            users[i] = *user;
            break;
        }
    }

    // Update antrian dokter
    Dokter *dokterTerpilih = map->dokter[pilihan - 1];
    dokterTerpilih->queueLength++;

    if (dokterTerpilih->jumlahPasienDalamRuangan <= map->maxPasienDalamRuangan) {
        dokterTerpilih->jumlahPasienDalamRuangan++;
    } else {
        dokterTerpilih->jumlahPasienLuarRuangan++;
    }

    enqueue(dokterTerpilih->queue, *user);

    // Update Hospital Room
    int ruangan = dokterTerpilih->ruangan;
    int pasienId = user->identitas.id;

    for (int i = 0; i < rumahSakit->roomCount; i++) {
        if (rumahSakit->rooms[i].roomIndex == ruangan) {
            Room *room = &rumahSakit->rooms[i];
            if (room->patientCount < MAX_PATIENTS) {
                room->patients[room->patientCount++] = pasienId;
            } else {
                printf("Ruangan %d penuh, tidak bisa update Hospital.\n", ruangan);
            }
            break;
        }
    }

    // Gunakan nama dari dokterValid karena sudah valid
    char labelRuangan[5];
    dapatkanLabelRuangan(dokterTerpilih->ruangan, labelRuangan, map->cols);

    printf("\nPendaftaran check-up berhasil!\n");
    printf("Anda terdaftar pada antrian dokter: %s, di ruangan: %s\n", dokterValid->identitas.username, labelRuangan);
    printf("Posisi antrian Anda: %d\n", dokterTerpilih->queue->size);
}