#include "src/Model/model.h"
#include "src/Label/label.h"
#include "src/DataParser/dataParser.h"
#include "src/Laman/pasien.h"
#include "src/Laman/manager.h"
#include "src/Laman/dokter.h"
#include "src/Utils/save.h"
#include "src/Utils/load.h"
#include "src/Laman/Denah/denah.h"
#include "src/Auth/auth.h"
#include "src/Laman/LihatUser/lihatuser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void labelInput();
void waitForEnter();
void cleanInputBuffer();

User *user = NULL;
User *users = NULL;
Penyakit *penyakits = NULL;

int jumlah_user = 0;
int jumlah_penyakit = 0;

Pilihan pilihan;
PilihanPasien pilihanP;
PilihanManager pilihanM;
PilihanDokter pilihanD;

int isLoggedIn = 0;

int main(int argc, char *argv[])
{
    user = malloc(sizeof(User));
    if (!user)
    {
        perror("Gagal mengalokasikan user");
        return 1;
    }

    users = malloc(MAX_USER * sizeof(User));
    if (!users)
    {
        perror("Gagal mengalokasikan array user");
        free(user);
        return 1;
    }

    penyakits = malloc(MAX_USER * sizeof(Penyakit));
    if (!penyakits)
    {
        perror("Gagal mengalokasikan array penyakit");
        free(user);
        free(users);
        return 1;
    }

    if (argc < 2)
    {
        printf("Tidak ada nama folder yang diberikan!\n");
        printf("Usage : ./main <<nama_folder>>\n");
        free(user);
        free(users);
        free(penyakits);
        return 1;
    }

    const char *folder = argv[1];
    load(folder);
    printf("Selamat datang kembali di rumah sakit K01-N !\n\n");

    jumlah_user = jumlah_penyakit = 0;
    ParseTarget pt = {users, &jumlah_user};
    ParsePenyakit pp = {penyakits, &jumlah_penyakit};

    char user_path[256], penyakit_path[256];
    snprintf(user_path, sizeof(user_path), "data/%s/user.csv", folder);
    snprintf(penyakit_path, sizeof(penyakit_path), "data/%s/penyakit.csv", folder);

    CSVtoArr(user_path, handleUserRow, &pt);
    CSVtoArr(penyakit_path, handlePenyakitRow, &pp);

    if (jumlah_user > 0)
    {
        User *temp = realloc(users, jumlah_user * sizeof(User));
        if (temp)
            users = temp;
    }

    do
    {
        if (!isLoggedIn)
        {
            labelInput();

            switch (pilihan)
            {
            case LOGIN:
                isLoggedIn = login();
                break;
            case REGISTER:
                isLoggedIn = registerpasien();
                break;
            case LUPAPASSWORD:
                lupaPassword();
                break;
            case EXIT:
                break;
            }
        }

        if (isLoggedIn && user != NULL)
        {
            pilihanP = pilihanM = pilihanD = 0;

            if (strcasecmp(user->identitas.role, "PASIEN") == 0)
            {
                clearScreen();
                lamanPasien();

                switch (pilihanP)
                {
                case DAFTARCHECKUP:
                case ANTRIANSAYA:
                case MINUMOBAT:
                case MINUMPENAWAR:
                    waitForEnter();
                    break;
                case DENAHRUMAHSAKIT:
                    clearScreen();
                    tampilkanDenahRS("config.txt");
                    waitForEnter();
                    break;
                case LOGOUTP:
                    logout();
                    isLoggedIn = 0;
                    pilihanP = 0;
                    break;
                }
            }
            else if (strcasecmp(user->identitas.role, "MANAGER") == 0)
            {
                clearScreen();
                lamanManager();

                switch (pilihanM)
                {
                case DENAHRUMAHSAKITMANAGER:
                    clearScreen();
                    printf("\n>>> %s\n\n", "DENAH RUMAH SAKIT");
                    tampilkanDenahRS("config.txt");
                    waitForEnter();
                    break;
                case LIHATUSER:
                    clearScreen();
                    printf("\n>>> %s\n\n", "LIHAT USER");
                    lamanLihatUser();
                    waitForEnter();
                    break;
                case LOGOUTM:
                    logout();
                    isLoggedIn = 0;
                    pilihanM = 0;
                    break;
                }
            }
            else if (strcasecmp(user->identitas.role, "DOKTER") == 0)
            {
                clearScreen();
                // lamanDokter();

                switch (pilihanD)
                {
                case DIAGNOSIS:
                case NGOBATIN:
                    waitForEnter();
                    break;
                case LOGOUTD:
                    logout();
                    isLoggedIn = 0;
                    pilihanD = 0;
                    break;
                }
            }

            if (!isLoggedIn && user == NULL)
            {
                user = malloc(sizeof(User));
                if (!user)
                {
                    perror("Gagal mengalokasikan ulang user");
                    return 1;
                }
            }
        }

    } while (pilihan != EXIT);

    clearScreen();
    char c;
    do
    {
        printf("\nApakah Anda mau melakukan penyimpanan file yang sudah diubah?(y/n)\n");
        scanf(" %c", &c);
        if (c == 'y' || c == 'Y')
        {
            char folder_name[MAX_LINE_LEN];
            printf("Masukkan nama folder penyimpanan (misal: RSMitraKasih): ");
            scanf("%s", folder_name);
            save(folder_name);
        }
    } while (c != 'y' && c != 'n' && c != 'Y' && c != 'N');

    clearScreen();
    printf("\nTerima kasih telah menggunakan sistem! <3\n\n");

    if (user)
        free(user);
    if (users)
        free(users);
    if (penyakits)
        free(penyakits);

    return 0;
}

void labelInput()
{
    extern Pilihan pilihan;
    int input, valid = 0;

    while (!valid)
    {
        clearScreen();
        labelRS();
        labelMenu();
        printf(">>> Masukkan pilihan (1-4): ");
        if (scanf("%d", &input) != 1)
        {
            cleanInputBuffer();
            printf("\nInput tidak valid! Masukkan angka antara 1-4.\n");
            waitForEnter();
            continue;
        }

        if (input < 1 || input > 4)
        {
            printf("\nInput di luar rentang! Masukkan angka antara 1-4.\n");
            waitForEnter();
            continue;
        }

        pilihan = (input == 4) ? EXIT : input;
        valid = 1;
    }

    const char *opsi[] = {"", "LOGIN", "REGISTER", "LUPA PASSWORD"};
    if (pilihan != EXIT)
        printf("\n>>> %s\n\n", opsi[pilihan]);
}

void cleanInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void waitForEnter()
{
    printf("\nTekan Enter untuk kembali ke menu...");
    cleanInputBuffer();
    getchar();
    clearScreen();
}
