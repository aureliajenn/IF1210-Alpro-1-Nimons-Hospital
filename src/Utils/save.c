#include "main.h"

void make_folder(const char* path) {
    char command[256];
    sprintf(command, "mkdir -p %s", path);
    system(command);
}

void save(const char folder_name[]) {
    extern User *users;
    extern int jumlah_user;
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

    // Load users dulu dari file lama
    char original_path[300];
    sprintf(original_path, "data/user.csv"); // atau path CSV lama
    // CSVtoArr(users, &jumlah_user, original_path);  // untuk menyimpan ulang

    FILE* userfile = fopen(test_file, "w");
    if (userfile != NULL) {
        fprintf(userfile, "id;username;password;role;riwayat_penyakit;suhu_tubuh;tekanan_darah_sistolik;tekanan_darah_diastolik;detak_jantung;saturasi_oksigen;kadar_gula_darah;berat_badan;tinggi_badan;kadar_kolesterol;kadar_kolesterol_ldl;trombosit\n");
        for (int i = 0; i < jumlah_user; i++) {
            // Tulis setiap baris User
            
            fprintf(userfile, "%d;%s;%s;%s;%s;%.2f;%d;%d;%d;%.2f;%d;%.2f;%d;%d;%d;%d\n",
            i+1,
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
        printf("Berhasil menyimpan data di folder %s!\n", full_path);
    } else {
        printf("Gagal menyimpan file di %s\n", full_path);
    }
}
