#include "main.h"

int login()
{
    extern User *user;
    extern User *users;
    extern int jumlah_user;
    int valid = 0, format;
    char nama[MAX_LINE_LEN], role[MAX_LINE_LEN];

    clearscreen();
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
                clearscreen();
                printf("\nUsername atau password salah untuk pengguna %s!\n", nama);
                waitForEnter();
                return 0;
            }
        }
    }

    if (!valid)
    {
        clearscreen();
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

int registerpasien() {
    extern User *user;
    extern User *users;
    extern int jumlah_user;

    int format, valid = 1;

    // Buat user baru sementara
    User *newUser = malloc(sizeof(User));
    if (!newUser) {
        perror("Gagal mengalokasikan memori untuk user baru");
        return 0;
    }

    // Input username dan validasi format
    cekFormatUsn(&format, newUser);

    // Cek apakah username sudah dipakai
    for (int i = 0; i < jumlah_user; i++) {
        if (strcasecmp(users[i].identitas.username, newUser->identitas.username) == 0) {
            valid = 0;
            break;
        }
    }

    if (!valid) {
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", newUser->identitas.username);
        waitForEnter();
        free(newUser);
        return 0;
    }

    // Kalau valid, input password dan lanjut proses
    printf("Password: ");
    scanf("%s", newUser->identitas.password);

    int highest = idTertinggi();
    newUser->identitas.id = highest + 1;
    strcpy(newUser->identitas.role, "pasien");

    // Inisialisasi kondisi kesehatan
    newUser->kondisi.jumlahObat = 0;
    newUser->kondisi.perut.top = -1;
    newUser->kondisi.sudahDiagnosis = 0;
    newUser->kondisi.sudahDiobati = 0;

    // Reallocate array users
    users = realloc(users, (jumlah_user + 1) * sizeof(User));
    if (!users) {
        perror("Gagal menambahkan pasien baru");
        free(newUser);
        exit(1);
    }

    // Copy newUser ke array users dan ke pointer global user
    users[jumlah_user] = *newUser;
    if (user != NULL) free(user);  // Bebaskan user lama jika ada
    user = newUser; // Simpan pointer global user untuk sesi login

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

    clearscreen();
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