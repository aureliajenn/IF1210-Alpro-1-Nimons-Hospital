#include "manager.h"

void lamanManager()
{
    extern User *user;
    extern PilihanManager pilihanM;
    int input;
    int valid = 0;

    while (!valid)
    {
        clearScreen();
        labelUser();
        printf("\nSelamat datang %s! Ada yang bisa saya bantu?\n\n", user->identitas.username);
        labelMenuManager();
        printf(">>> Masukkan pilihan (1-3): ");

        int ret = scanf("%d", &input);

        if (ret != 1)
        {
            while (getchar() != '\n')
                printf("\nInput tidak valid! Masukkan angka antara 1-5.");
            printf("\nSilahkan enter untuk mengulang!\n");
            getchar();
            continue;
        }

        switch (input)
        {
        case 1:
        case 2:
            pilihanM = input;
            valid = 1;
            break;
        case 3:
        {
            char c;
            int confirmLogout = 0;

            while (!confirmLogout)
            {
                printf("Yakin mau logout? (y/n): ");
                scanf(" %c", &c);
                if (c == 'y' || c == 'Y')
                {
                    pilihanM = LOGOUTM;
                    valid = 1;
                    confirmLogout = 1;
                }
                else if (c == 'n' || c == 'N')
                {
                    printf("\nLogout dibatalkan. Tekan ENTER untuk kembali ke menu.\n");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    confirmLogout = 1;
                }
                else
                {
                    printf("\nInput tidak valid! Masukkan 'y' atau 'n'.\n");
                }
            }
            break;
        }

        default:
            printf("\nPilihan tidak valid! Silakan ulangi.\n");
            getchar();
        }
    }

    char *opsi[] = {"", "DENAH RUMAH SAKIT", "LIHAT USER"};
    if (pilihanM != LOGOUTM)
        printf("\n>>> %s\n\n", opsi[pilihanM]);
}