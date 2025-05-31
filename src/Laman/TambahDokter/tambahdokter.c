#include "main.h"

int lamanTambahDokter() {
    extern User *user;
    extern User *users;
    extern int jumlah_user;
    int format, valid = 1;
    
    // Buat user temporary untuk input baru, jangan ubah user global
    User *temp_user = malloc(sizeof(User));
    if (!temp_user) {
        printf("Gagal mengalokasikan memori untuk user baru.\n");
        return 0;
    }
    
    cekFormatUsn(&format, temp_user);
    
    // Cek apakah username sudah ada
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
    
    // Realokasi array users untuk menambah dokter baru
    User *temp_users = realloc(users, (jumlah_user + 1) * sizeof(User));
    if (!temp_users) {
        perror("Gagal menambahkan dokter baru");
        free(temp_user);
        return 0;
    }
    users = temp_users;
    
    // Input password
    printf("Password: ");
    scanf("%s", temp_user->identitas.password);
    
    // Tambahkan dokter baru ke array
    strcpy(users[jumlah_user].identitas.username, temp_user->identitas.username);
    strcpy(users[jumlah_user].identitas.password, temp_user->identitas.password);
    strcpy(users[jumlah_user].identitas.role, "DOKTER");
    
    jumlah_user++;
    printf("Dokter %s berhasil ditambahkan!\n", temp_user->identitas.username);
    
    // Bersihkan memori temporary
    free(temp_user);
    
    return 1;
}