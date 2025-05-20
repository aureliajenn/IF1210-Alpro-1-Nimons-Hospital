#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // Untuk cek folder
#include "../Model/model.h"
#include "../DataParser/dataParser.h"

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
