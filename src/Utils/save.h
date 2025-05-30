#pragma once

#define MAX_USER 100
#define MAX_LINE_LEN 1024

void copy_file(const char *src, const char *dest);

int hitungPasienPunyaInventory(User* users, int jumlah_user) ;

int hitungPasienPunyaObatDalamPerut(User* users, int jumlah_user) ;

void make_folder(const char* path);

void save(const char folder_name[],const char folder_asal[]);