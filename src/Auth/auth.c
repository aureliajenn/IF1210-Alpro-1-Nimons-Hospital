#include "auth.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



int login()
{
    extern User *user;
    extern User *users;
    extern int jumlah_user;
    int valid = 0, format;
    char nama[MAX_LINE_LEN], role[MAX_LINE_LEN];

    if (user == NULL)
        user = malloc(sizeof(User));

    clearScreen();
    cekFormatUsn(&format, user);
    strcpy(nama, user->identitas.username);

    printf("Password: ");
    scanf("%s", user->identitas.password);

    for (int i = 0; i < jumlah_user; i++)
    {
        if (strcasecmp(users[i].identitas.username, user->identitas.username) == 0)
        {
            if (strcmp(users[i].identitas.password, user->identitas.password) == 0)
            {
                valid = 1;
                strcpy(user->identitas.role, users[i].identitas.role);
                strcpy(role, user->identitas.role);
                break;
            }
            else
            {
                clearScreen();
                printf("\nUsername atau password salah untuk pengguna %s!\n", nama);
                waitForEnter();
                return 0;
            }
        }
    }

    if (!valid)
    {
        clearScreen();
        printf("\nTidak ada pengguna dengan username %s!\n", nama);
        waitForEnter();
        return 0;
    }

    printf("\nSelamat pagi %s %s!\n", role, nama);
    printf("\nSedang memuat laman %s...\n", role);
    return 1;
}

void logout()
{
    extern User *user;
    if (user != NULL)
    {
        free(user);
        user = NULL;
    }
}

int registerpasien()
{
    extern User *user;
    extern User *users;
    extern int jumlah_user;
    int format, valid = 1;

    if (user == NULL)
        user = malloc(sizeof(User));

    clearScreen();
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
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", user->identitas.username);
        waitForEnter();
        free(user);
        user = NULL;
        return 0;
    }

    users = realloc(users, (jumlah_user + 1) * sizeof(User));
    if (!users)
    {
        perror("Gagal menambahkan pasien baru");
        exit(1);
    }

    printf("Password: ");
    scanf("%s", user->identitas.password);
    strcpy(users[jumlah_user].identitas.username, user->identitas.username);
    strcpy(users[jumlah_user].identitas.password, user->identitas.password);
    strcpy(users[jumlah_user].identitas.role, "PASIEN");
    strcpy(user->identitas.role, "PASIEN");

    jumlah_user++;
    printf("Pasien %s berhasil ditambahkan!\n", user->identitas.username);
    return 1;
}

void runLengthEncode(char *input, char *output)
{
    int len = strlen(input);
    int count = 1;
    int index = 0;

    for (int i = 1; i <= len; i++)
    {
        if (input[i] == input[i - 1])
        {
            count++;
        }
        else
        {
            output[index++] = input[i - 1];
            output[index++] = count + '0';
            count = 1;
        }
    }
    output[index] = '\0';
}

void lupaPassword()
{
    extern User *users;
    extern int jumlah_user;

    char username[MAX_LINE_LEN];
    char newPassword[MAX_LINE_LEN];
    char kodeUnik[MAX_LINE_LEN];
    int found = 0;

    clearScreen();
    printf(">>>Lupa Password\n\n");

    printf("Masukkan username Anda: ");
    scanf("%s", username);

    runLengthEncode(username, kodeUnik);
    printf("Kode Unik: %s\n", kodeUnik);

    for (int i = 0; i < jumlah_user; i++)
    {
        char validKodeUnik[MAX_LINE_LEN];
        runLengthEncode(users[i].identitas.username, validKodeUnik);

        if (strcasecmp(users[i].identitas.username, username) == 0)
        {
            found = 1;
            printf("Username ditemukan.\n");
            printf("Masukkan password baru: ");
            scanf("%s", newPassword);
            strcpy(users[i].identitas.password, newPassword);
            printf("Password berhasil diubah untuk %s.\n", username);
            return;
        }
    }

    if (!found)
    {
        printf("Username tidak ditemukan!\n");
        waitForEnter();
    }
}
