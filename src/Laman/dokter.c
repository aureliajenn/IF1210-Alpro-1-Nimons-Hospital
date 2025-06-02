#include "main.h"

void lamanDokter(){
    extern User *user;
    extern PilihanDokter pilihanD;
    int input;
    int valid = 0;

    while (!valid) {
        clearscreen();
        labelUser();
        printf("\nSelamat pagi %s! Siap untuk bekerja?\n\n",user->identitas.username);
        labelDokter();
        printf(">>> Masukkan pilihan (1-3): ");
        
        int ret = scanf("%d", &input);

        if(ret != 1){
            while(getchar() != '\n'); // flush input buffer
            printf("\nInput tidak valid! Masukkan angka antara 1-3.");
            printf("\nSilahkan enter untuk mengulang!\n");
            getchar(); // tunggu enter
            continue;
        }
        else if (input != 1 && input != 2 && input != 3){
            // input bukan angka
            while(getchar() != '\n'); // flush input buffer
            printf("\nInput tidak valid! Masukkan angka antara 1-3.");
            printf("\nSilahkan enter untuk mengulang!\n");
            getchar(); // tunggu enter
            continue;
        }

        switch (input) {
            case 1: case 2:
                pilihanD = input;
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
                            pilihanD = LOGOUTD;
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
                getchar(); // tunggu enter
        }
    }
}

