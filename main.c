#include "main.h"

void labelInput();
void waitForEnter();
void cleanInputBuffer();

User *user = NULL;
User *users = NULL;
Penyakit *penyakits = NULL;
Map *map = NULL;
Hospital *rumahSakit = NULL;
Obat *obats = NULL;

int jumlah_obat = 0;
int jumlah_user = 0;
int jumlah_penyakit = 0;

Pilihan pilihan;
PilihanPasien pilihanP;
PilihanManager pilihanM;
PilihanDokter pilihanD;

int isLoggedIn = 0;
// void debugPrintInventory(User u) {
//     printf("Inventory User ID %d (%s):\n", u.identitas.id, u.identitas.username);
//     for (int i = 0; i < u.kondisi.jumlahObat; i++) {
//         printf(" %d - %s\n",u.kondisi.jumlahObat, u.kondisi.inventory[i].nama);
//     }
// }
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

    obats = malloc(MAX_OBAT * sizeof(Obat));
    if (!obats)
    {
        perror("Gagal mengalokasikan array Obat");
        free(user);
        free(obats);
        return 1;
    }

    penyakits = malloc(MAX_USER * sizeof(Penyakit));
    if (!penyakits)
    {
        perror("Gagal mengalokasikan array penyakit");
        free(user);
        free(obats);
        free(users);
        return 1;
    }

    if (argc < 2)
    {
        printf("Tidak ada nama folder yang diberikan!\n");
        printf("Usage : ./main <<nama_folder>>\n");
        free(user);
        free(users);
        free(obats);
        free(penyakits);
        return 1;
    }

    const char *folder = argv[1];
    load(folder);

//     for (int i = 0; i < jumlah_user; i++) {
//     debugPrintInventory(users[i]);
// }

    do
    {
      
        if (!isLoggedIn)
        {
            //clearscreen();
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
                //clearscreen();
                lamanPasien();

                switch (pilihanP)
                {
                case DAFTARCHECKUP:
                    //clearscreen();
                    printf("\n>>> %s\n\n", "DAFTAR CHECKUP");
                    flush_stdin();
                    daftar_checkup();
                    waitForEnter();
                    break;
                case ANTRIANSAYA:
                    //clearscreen();
                    printf("\n>>> %s\n\n", "ANTRIAN SAYA");
                    lamanLihatAntrianSaya();
                    waitForEnter();
                    break;
                case MINUMOBAT:
                    //clearscreen();
                    printf("\n>>> %s\n\n", "MINUM OBAT");
                    lamanMinumObat();
                    waitForEnter();
                    break;
                case MINUMPENAWAR:
                    waitForEnter();
                    break;
                case DENAHRUMAHSAKIT:
                    //clearscreen();
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
                //clearscreen();
                lamanManager();

                switch (pilihanM)
                {
                case DENAHRUMAHSAKITMANAGER:
                    //clearscreen();
                    printf("\n>>> %s\n\n", "DENAH RUMAH SAKIT");
                    tampilkanDenahRS();
                    waitForEnter();
                    break;
                case LIHATUSER:
                    //clearscreen();
                    printf("\n>>> %s\n\n", "LIHAT USER");
                    lamanLihatUser();
                    waitForEnter();
                    break;
                case CARIUSER:
                    //clearscreen();
                    printf("\n>>> %s\n\n", "CARI USER");
                    lamanCariUser(-1);
                    waitForEnter();
                    break;
                case TAMBAHDOKTER:
                    //clearscreen();
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
                //clearscreen();
                lamanDokter();

                switch (pilihanD)
                {
                case DIAGNOSIS:
                    //clearscreen();
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

    //clearscreen();
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

    //clearscreen();
    printf("\nTerima kasih telah menggunakan sistem! <3\n\n");

    if (user) free(user);
    if (users) free(users);
    if (penyakits) free(penyakits);
    if (obats) free(obats);
    if (map) free(map);
    if (rumahSakit) free(rumahSakit);

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
    //clearscreen();
}
