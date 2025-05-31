#include "main.h"

void lamanPasien()
{
    extern User *user;
    extern PilihanPasien pilihanP;
    int input;
    int valid = 0;

    while (!valid)
    {
        //clearscreen();
        labelUser();
        printf("\nSelamat pagi %s! Ada keluhan apa?\n\n", user->identitas.username);
        labelMenuPasien();
        printf(">>> Masukkan pilihan (1-6): ");

        int ret = scanf("%d", &input);

        if (ret != 1)
        {
            while (getchar() != '\n')
                ; // flush input buffer
            printf("\nInput tidak valid! Masukkan angka antara 1-5.");
            printf("\nSilahkan enter untuk mengulang!\n");
            getchar(); // tunggu enter
            continue;
        }
        else if (input != 1 && input != 2 && input != 3 && input != 4 && input != 5 && input != 6)
        {
            // input bukan angka
            while (getchar() != '\n')
                ; // flush input buffer
            printf("\nInput tidak valid! Masukkan angka antara 1-5.");
            printf("\nSilahkan enter untuk mengulang!\n");
            getchar(); // tunggu enter
            continue;
        }

        switch (input)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            pilihanP = input;
            valid = 1;
            break;
        case 6:
        {
            char c;
            int confirmLogout = 0;

            while (!confirmLogout)
            {
                printf("Yakin mau logout? (y/n): ");
                scanf(" %c", &c);
                if (c == 'y' || c == 'Y')
                {
                    pilihanP = LOGOUTP;
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
}
