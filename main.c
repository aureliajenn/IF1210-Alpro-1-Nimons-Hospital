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
#include "src/Laman/CariUser/cariuser.h"
#include "src/Laman/TambahDokter/tambahdokter.h"
#include "src/Laman/daftarcheckup/daftar_checkup.h"
#include "src/Laman/AntrianSaya/antriansaya.h"
#include "src/Laman/Diagnosis/diagnosis.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void labelInput();
void waitForEnter();
void cleanInputBuffer();

User *user = NULL;
User *users = NULL;
Penyakit *penyakits = NULL;
Map *map = NULL;
Hospital *rumahSakit = NULL;

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

    rumahSakit = malloc(sizeof(Hospital));
    if (!rumahSakit)
    {
        perror("Gagal mengalokasikan RS");
        return 1;
    }

    map = malloc(sizeof(Map));
    if (!map)
    {
        perror("Gagal mengalokasikan map");
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
            clearScreen();
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
                    clearScreen();
                    printf("\n>>> %s\n\n", "DAFTAR CHECKUP");
                    daftar_checkup();
                    waitForEnter();
                    break;
                case ANTRIANSAYA:
                    clearScreen();
                    printf("\n>>> %s\n\n", "ANTRIAN SAYA");
                    lamanLihatAntrianSaya();
                    waitForEnter();
                    break;
                case MINUMOBAT:
                case MINUMPENAWAR:
                    waitForEnter();
                    break;
                case DENAHRUMAHSAKIT:
                    clearScreen();
                    tampilkanDenahRS();
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
                    tampilkanDenahRS();
                    waitForEnter();
                    break;
                case LIHATUSER:
                    clearScreen();
                    printf("\n>>> %s\n\n", "LIHAT USER");
                    lamanLihatUser();
                    waitForEnter();
                    break;
                case CARIUSER:
                    clearScreen();
                    printf("\n>>> %s\n\n", "CARI USER");
                    lamanCariUser(-1);
                    waitForEnter();
                    break;
                case TAMBAHDOKTER:
                    clearScreen();
                    printf("\n>>> %s\n\n", "TAMBAH DOKTER");
                    lamanTambahDokter();
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
                lamanDokter();

                switch (pilihanD)
                {
                case DIAGNOSIS:
                    clearScreen();
                    printf("\n>>> %s\n\n", "DIAGNOSIS");
                    lamanDiagnosis();
                    waitForEnter();
                    break;
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
    labelRS();
    labelMenu();
    pilihan = getValidIntInput(1, 4, "Pilih opsi (1-4): ");
}



void waitForEnter()
{
    printf("\nTekan Enter untuk kembali ke menu...");
    cleanInputBuffer();
    getchar();
    clearScreen();
}
