#include "tambahdokter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




int lamanTambahDokter()
{
    extern User *user;
    extern User *users;
    extern int jumlah_user;
    int format, valid = 1;

    if (user == NULL)
        user = malloc(sizeof(User));

    cekFormatUsn(&format, user);

    for (int i = 0; i < jumlah_user; i++)
    {
        if (strcasecmp(users[i].identitas.username, user->identitas.username) == 0)
        {
            valid = 0;
            break;
        }
    }

    if (!valid)
    {
        clearScreen();
        printf("Registrasi gagal! Dokter dengan nama %s sudah terdaftar.\n", user->identitas.username);
        waitForEnter();
        free(user);
        user = NULL;
        return 0;
    }

    users = realloc(users, (jumlah_user + 1) * sizeof(User));
    if (!users)
    {
        perror("Gagal menambahkan dokter baru");
        exit(1);
    }

    printf("Password: ");
    scanf("%s", user->identitas.password);
    strcpy(users[jumlah_user].identitas.username, user->identitas.username);
    strcpy(users[jumlah_user].identitas.password, user->identitas.password);
    strcpy(users[jumlah_user].identitas.role, "DOKTER");
    strcpy(user->identitas.role, "DOKTER");

    jumlah_user++;
    printf("Dokter %s berhasil ditambahkan!\n", user->identitas.username);
    printf("Fitur ini belum tersedia.\n");
    return 1;
    
}

