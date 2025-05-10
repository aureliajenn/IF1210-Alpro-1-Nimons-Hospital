#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load(const char *folder_name){
    char path_user[256], path_config[256];

    sprintf(path_user, "%s/user.csv", folder_name);
    sprintf(path_config,"%s/config.txt", folder_name);

    FILE *file_user = fopen(path_user,"r");
    FILE *file_config = fopen(path_config,"r");

    if (!file_user || !file_config){
        printf("Folder \"%s\" tidak ditemukan.\n", folder_name);
        if (file_user){
            fclose(file_user);
        }
        if (file_config){
            fclose(file_config);
        }
        exit(EXIT_FAILURE);
    }
    printf("Loading...\n");
    printf("Selamat datang kembali di rumah sakit Nimons!\n");

    fclose(file_user);
    fclose(file_config);
}
