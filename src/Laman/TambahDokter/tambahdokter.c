#include "main.h"

int lamanTambahDokter() {
    extern User *users;
    extern Map *map;
    extern int jumlah_user;

    int format, valid = 1;

    User *temp_user = malloc(sizeof(User));
    if (!temp_user) {
        printf("Gagal mengalokasikan memori untuk user baru.\n");
        return 0;
    }

    cekFormatUsn(&format, temp_user);

    for (int i = 0; i < jumlah_user; i++) {
        if (strcasecmp(users[i].identitas.username, temp_user->identitas.username) == 0) {
            valid = 0;
            break;
        }
    }

    if (!valid) {
        printf("Registrasi gagal! Dokter dengan nama %s sudah terdaftar.\n", temp_user->identitas.username);
        free(temp_user);
        return 0;
    }

    User *temp_users = realloc(users, (jumlah_user + 1) * sizeof(User));
    if (!temp_users) {
        perror("Gagal menambahkan dokter baru");
        free(temp_user);
        return 0;
    }
    users = temp_users;

    printf("Password: ");
    scanf("%s", temp_user->identitas.password);

    // Tambahkan data user baru
    strcpy(users[jumlah_user].identitas.username, temp_user->identitas.username);
    strcpy(users[jumlah_user].identitas.password, temp_user->identitas.password);
    strcpy(users[jumlah_user].identitas.role, "dokter");
    int idBaru = idTertinggi() + 1;
    users[jumlah_user].identitas.id = idBaru;

    // *** Buat objek Dokter baru ***
    Dokter *dokterBaru = malloc(sizeof(Dokter));
    if (!dokterBaru) {
        printf("Gagal mengalokasikan memori untuk dokter baru.\n");
        free(temp_user);
        return 0;
    }
    dokterBaru->id = idBaru;
    dokterBaru->ruangan = -1;  // default belum ada ruangan
    dokterBaru->queue = createQueue();
    dokterBaru->queueLength=0;
    dokterBaru->queueLengthNg=0;

    // *** Masukkan dokter ke map ***
    if (!insertDoctor(map, dokterBaru)) {
        printf("Map penuh, tidak dapat menambahkan dokter baru.\n");
        free(dokterBaru);
        free(temp_user);
        return 0;
    }

    // Assign dokter ke ruangan
    assignDokter(&users[jumlah_user]);

    // Cek apakah assign ruangan berhasil
    if (dokterBaru->ruangan == -1) {
        // Rollback dokter dari map
        printf("Gagal assign ruangan. Dokter %s tidak ditambahkan ke sistem.\n", temp_user->identitas.username);

        // Hapus dokter dari map
        for (int i = 0; i < map->size; i++) {
            if (map->dokter[i]->id == idBaru) {
                free(map->dokter[i]);
                for (int j = i; j < map->size - 1; j++) {
                    map->dokter[j] = map->dokter[j + 1];
                }
                map->size--;
                break;
            }
        }

        // Hapus user juga
        return 0;
    }

    jumlah_user++;
    printf("Dokter %s berhasil ditambahkan!\n", temp_user->identitas.username);

    free(temp_user);
    return 1;
}

void assignDokter(User *dokterUser) {
    extern Hospital *rumahSakit;
    extern Map *map;
    extern User *users;
    extern int jumlah_user;

    char kodeRuangan[10];

    printf("Ruangan: ");
    scanf("%s", kodeRuangan);

    Dokter *dokter = getDoctor(map, dokterUser->identitas.id);
    if (!dokter) {
        printf("Dokter %s belum terdaftar di sistem.\n", dokterUser->identitas.username);
        return;
    }

    int idxRuangan = ruanganStringToInt(kodeRuangan, rumahSakit->cols);
    if (idxRuangan < 0 || idxRuangan >= rumahSakit->rows * rumahSakit->cols) {
        printf("Kode ruangan tidak valid.\n");
        return;
    }

    Room *targetRoom = &rumahSakit->rooms[idxRuangan];

    if (dokter->ruangan != -1) {
        // Kasus 2 atau 4
        char label[10];
        dapatkanLabelRuangan(dokter->ruangan, label, rumahSakit->cols);

        if (targetRoom->doctorId == -1 || targetRoom->doctorId == dokter->id) {
            printf("Dokter %s sudah diassign ke ruangan %s!\n", dokterUser->identitas.username, label);
        } else {
            char label2[10];
            dapatkanLabelRuangan(idxRuangan, label2, rumahSakit->cols);
            const char *penghuniLama = dapatkanUsername(users, jumlah_user, targetRoom->doctorId, "dokter");
            printf("Dokter %s sudah menempati ruangan %s!\n", dokterUser->identitas.username, label);
            printf("Ruangan %s juga sudah ditempati dokter %s!\n", label2, penghuniLama);
        }
        return;
    }

    if (targetRoom->doctorId == -1 || targetRoom->doctorId == 0) {
        // Kasus 1
        dokter->ruangan = idxRuangan;
        targetRoom->doctorId = dokter->id;
        printf("Dokter %s berhasil diassign ke ruangan %s!\n", dokterUser->identitas.username, kodeRuangan);
    } else {
        // Kasus 3
        const char *penghuniLama = dapatkanUsername(users, jumlah_user, targetRoom->doctorId, "dokter");
        printf("Dokter %s sudah menempati ruangan %s!\n", penghuniLama, kodeRuangan);
        printf("Silakan cari ruangan lain untuk dokter %s.\n", dokterUser->identitas.username);
    }
}

int ruanganStringToInt(const char *kode, int cols) {
    if (strlen(kode) < 2) return -1;
    int row = kode[0] - 'A';
    int col = atoi(kode + 1) - 1;
    if (row < 0 || col < 0 || col >= cols) return -1;
    return row * cols + col;
}