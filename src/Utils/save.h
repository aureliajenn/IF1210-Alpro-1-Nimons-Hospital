#ifndef SAVE_H
#define SAVE_H

#define MAX_USER 100
#define MAX_LINE_LEN 1024

typedef struct {
    int id;
    char username[MAX_LINE_LEN];
    char password[MAX_LINE_LEN];
    char role[MAX_LINE_LEN];
    char riwayat_penyakit[MAX_LINE_LEN];
    
} Identitas;

void make_folder(const char* path);

void save(char* folder_name);

#endif