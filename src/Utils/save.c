#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save.h"

void make_folder(const char* path[]) {
    char command[256];
    sprintf(command, "mkdir -p %s", path);
    system(command);
}

void save(char* folder_name[]) {
    char base_path[] = "data";
    char full_path[300];
    sprintf(full_path, "%s/%s", base_path, folder_name);

    FILE* test_data = fopen(base_path, "r");
    if (test_data == NULL) {
        printf("Membuat folder %s...\n", base_path);
        make_folder(base_path);
    } else {
        fclose(test_data);
    }

    char test_file[320];
    sprintf(test_file, "%s/user.csv", full_path);
    FILE* test = fopen(test_file, "r");

    if (test == NULL) {
        printf("Membuat folder %s...\n", full_path);
        buat_folder(full_path);
        printf("Saving...\n");
    } else {
        fclose(test);
        printf("Saving...\n");
    }

    FILE* userfile = fopen(test_file, "w");
    if (userfile != NULL) {
        Identitas users[MAX_USER];
        int userCount = 0;
        fprintf(userfile, "id;username;role\n");
        for (int i = 0; i < userCount; i++) {
            fprintf(userfile, "%s;%s;%s\n", users[i].id, users[i].username, users[i].role);
        }
        fclose(userfile);
        printf("Berhasil menyimpan data di folder %s!\n", full_path);
    } else {
        printf("Gagal menyimpan file di %s\n", full_path);
    }
}
