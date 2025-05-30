#include "main.h"

int login()
{
    extern User *user;
    extern User *users;
    extern int jumlah_user;
    int valid = 0, format;
    char nama[MAX_LINE_LEN], role[MAX_LINE_LEN];

    //clearscreen();
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
                user = &users[i];
                strcpy(role, user->identitas.role);
                break;
            }
            else
            {
                //clearscreen();
                printf("\nUsername atau password salah untuk pengguna %s!\n", nama);
                waitForEnter();
                return 0;
            }
        }
    }

    if (!valid)
    {
        //clearscreen();
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

    //clearscreen();
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
        //clearscreen();
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
    char inputKodeUnik[MAX_LINE_LEN];
    char expectedKodeUnik[MAX_LINE_LEN];
    int found = 0;

    //clearscreen();
    printf(">>> Lupa Password\n\n");

    printf("Masukkan username Anda: ");
    scanf("%s", username);

    for (int i = 0; i < jumlah_user; i++)
    {
        if (strcasecmp(users[i].identitas.username, username) == 0)
        {
            found = 1;
            // Buat kode unik dari username yang ditemukan
            runLengthEncode(users[i].identitas.username, expectedKodeUnik);

            printf("Masukkan kode unik Anda (berdasarkan username): ");
            scanf("%s", inputKodeUnik);

            if (strcmp(inputKodeUnik, expectedKodeUnik) == 0)
            {
                printf("Kode unik benar.\n");
                printf("Masukkan password baru: ");
                scanf("%s", newPassword);
                strcpy(users[i].identitas.password, newPassword);
                printf("Password berhasil diubah untuk %s.\n", username);
            }
            else
            {
                printf("Kode unik salah! Tidak bisa mengganti password.\n");
            }
            return;
        }
    }

    if (!found)
    {
        printf("Username tidak ditemukan!\n");
    }
}