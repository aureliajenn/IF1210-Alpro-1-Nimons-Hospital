#include "dokter.h"
#include "../Model/model.h"

void lamanDokter(){
    extern User *user;
    extern PilihanDokter pilihanD;
    int input;
    int valid = 0;

    while (!valid) {
        clearScreen();
        labelUser();
        printf("\nSelamat pagi %s! Ada keluhan apa?\n\n",user->identitas.username);
        labelMenuPasien();
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
                char c;
                do{
                    printf("Yakin mau logout? (y/n)\n");
                    scanf(" %c",&c);
                    if(c=='n' || c=='N'){
                        lamanPasien();
                    }
                }while(c != 'y' && c != 'n' && c != 'Y' && c != 'N');
                pilihanD = LOGOUTP;
                valid = 1;
                break;
            default:
                printf("\nPilihan tidak valid! Silakan ulangi.\n");
                getchar(); // tunggu enter
        }
    }

    char *opsi[] = {"", "DIAGNOSIS", "NGOBATIN"};
    if (pilihanD != LOGOUTD)
        printf("\n>>> %s\n\n", opsi[pilihanD]);
}

