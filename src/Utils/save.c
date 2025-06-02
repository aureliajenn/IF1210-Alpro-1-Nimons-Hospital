#include "main.h"
#include <unistd.h>  // untuk access()
#include <errno.h>

void copy_file(const char *src, const char *dest) {
    FILE *source = fopen(src, "r");
    if (!source) {
        fprintf(stderr, "Gagal membuka sumber: %s\n", src);
        return;
    }

    FILE *destination = fopen(dest, "w");
    if (!destination) {
        fprintf(stderr, "Gagal membuat salinan ke: %s\n", dest);
        fclose(source);
        return;
    }

    char buffer[BUFSIZ];
    size_t n;
    while ((n = fread(buffer, 1, BUFSIZ, source)) > 0) {
        fwrite(buffer, 1, n, destination);
    }

    fclose(source);
    fclose(destination);
}

int hitungPasienPunyaInventory(User* users, int jumlah_user) {
    int count = 0;
    for (int i = 0; i < jumlah_user; i++) {
        if (users[i].kondisi.jumlahObat > 0 && strcasecmp(users[i].identitas.role, "pasien") == 0) {
            count++;
        }
    }
    return count;
}

int hitungPasienPunyaObatDalamPerut(User* users, int jumlah_user) {
    int count = 0;
    for (int i = 0; i < jumlah_user; i++) {
        if (users[i].kondisi.perut.top >= 0 && strcasecmp(users[i].identitas.role, "pasien") == 0) {
            count++;
        }
    }
    return count;
}

void make_folder(const char* path) {
    char command[256];
    sprintf(command, "mkdir -p %s", path);
    system(command);
}

void save(const char folder_name[],const char folder_asal[]) {
    extern User *users;
    extern int jumlah_user;
    extern Hospital *rumahSakit;
    extern Map *map;

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

    // --- Menyimpan user.csv ---
    FILE* userfile = fopen(test_file, "w");
    if (userfile != NULL) {
        fprintf(userfile, "id;username;password;role;riwayat_penyakit;suhu_tubuh;tekanan_darah_sistolik;tekanan_darah_diastolik;detak_jantung;saturasi_oksigen;kadar_gula_darah;berat_badan;tinggi_badan;kadar_kolesterol;trombosit\n");
        for (int i = 0; i < jumlah_user; i++) {
            fprintf(userfile, "%d;%s;%s;%s;%s;%.2f;%d;%d;%d;%.2f;%d;%.2f;%d;%d;%d\n",
                users[i].identitas.id,
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
                users[i].kondisi.trombosit
            );
        }
        fclose(userfile);
        printf("Berhasil menyimpan data user di folder %s!\n", full_path);
    } else {
        printf("Gagal menyimpan user.csv di %s\n", full_path);
    }

    // --- Menyimpan config.txt ---
    char config_path[MAX_LINE_LEN];
    sprintf(config_path, "%s/config.txt", full_path);
    FILE *config = fopen(config_path, "w");
    if (config == NULL) {
        printf("Gagal menyimpan config.txt di %s\n", config_path);
        return;
    }

    // Baris 1: ukuran rumah sakit
    fprintf(config, "%d %d\n", rumahSakit->rows, rumahSakit->cols);

    // Baris 2: kapasitas per ruangan dan antrian luar
    fprintf(config, "%d %d\n", rumahSakit->maxPatientsPerRoom, map->maxAntrianLuar);

    // Baris 3-8: kondisi tiap ruangan
    for (int i = 0; i < rumahSakit->roomCount; i++) {
    Room r = rumahSakit->rooms[i];
    if (r.doctorId == 0) {
        fprintf(config, "0\n");
        continue;
    }

    fprintf(config, "%d", r.doctorId); // ID dokter
    
    // Tulis pasien dalam ruangan
    if(r.patientCount==0){
        fprintf(config, " 0");
    }else
    {for (int j = 0; j < r.patientCount; j++) {
        if(r.patients[j]==0)continue;
        fprintf(config, " %d", r.patients[j]);
    }}

    fprintf(config, "\n");
    }

    // Simpan inventory obat pasien
    // Format: jumlah pasien yang punya inventory obat
    int jumlahInventory = hitungPasienPunyaInventory(users, jumlah_user);
    fprintf(config, "%d\n", jumlahInventory);
    for (int i = 0; i < jumlah_user; i++) {
        if (users[i].kondisi.jumlahObat > 0 && strcasecmp(users[i].identitas.role,"pasien")==0) {
            fprintf(config, "%d", users[i].identitas.id);
            for (int j = 0; j < users[i].kondisi.jumlahObat; j++) {
                fprintf(config, " %d", users[i].kondisi.inventory[j].id);
            }
            fprintf(config, "\n");
        }
    }

    // Simpan obat yang sudah diminum di perut pasien
    // Format: jumlah pasien yang punya perut obat
    int jumlahPerut = hitungPasienPunyaObatDalamPerut(users, jumlah_user);
    fprintf(config, "%d\n", jumlahPerut);
    for (int i = 0; i < jumlah_user; i++) {
        if (users[i].kondisi.perut.top >= 0 && strcasecmp(users[i].identitas.role,"pasien")==0) {
            fprintf(config, "%d", users[i].identitas.id);
            for (int j = 0; j <= users[i].kondisi.perut.top; j++) {
                fprintf(config, " %d", users[i].kondisi.perut.items[j].id);
            }
            fprintf(config, "\n");
        }
    }


    fclose(config);

        const char *static_files[] = {
        "obat.csv",
        "obat_penyakit.csv",
        "penyakit.csv",
        "README.txt"
    };

    for (int i = 0; i < 4; i++) {
        char src[MAX_LINE_LEN];
        char dest[MAX_LINE_LEN];
        sprintf(src, "data/%s/%s", folder_asal, static_files[i]);
        sprintf(dest, "data/%s/%s", folder_name, static_files[i]);
        copy_file(src, dest);
    }

    printf("Berhasil menyalin file statis ke %s!\n", folder_name);
    printf("Berhasil menyimpan config.txt ke %s!\n", folder_name);
}