#include "pasien.h"

void lamanPasien(){
    extern User *user;
    extern PilihanPasien pilihanP;
    int input;
    int valid = 0;

    while (!valid) {
        clearScreen();
        labelUser();
        printf("\nSelamat pagi %s! Ada keluhan apa?\n\n",user->identitas.username);
        labelMenuPasien();
        printf(">>> Masukkan pilihan (1-5): ");
        
        int ret = scanf("%d", &input);

        if(ret != 1){
            while(getchar() != '\n'); // flush input buffer
            printf("\nInput tidak valid! Masukkan angka antara 1-5.");
            printf("\nSilahkan enter untuk mengulang!\n");
            getchar(); // tunggu enter
            continue;
        }
        else if (input != 1 && input != 2 && input != 3 && input != 4 && input != 5){
            // input bukan angka
            while(getchar() != '\n'); // flush input buffer
            printf("\nInput tidak valid! Masukkan angka antara 1-5.");
            printf("\nSilahkan enter untuk mengulang!\n");
            getchar(); // tunggu enter
            continue;
        }

        switch (input) {
            case 1: case 2: case 3: case 4:
                pilihanP = input;
                valid = 1;
                break;
            case 5:
                char c;
                do{
                    printf("Yakin mau logout? (y/n)\n");
                    scanf(" %c",&c);
                    if(c=='n' || c=='N'){
                        lamanPasien();
                    }
                }while(c != 'y' && c != 'n' && c != 'Y' && c != 'N');
                pilihanP = LOGOUTP;
                valid = 1;
                break;
            default:
                printf("\nPilihan tidak valid! Silakan ulangi.\n");
                getchar(); // tunggu enter
        }
    }

    char *opsi[] = {"", "DAFTAR CHECK-UP", "ANTRIAN SAYA", "MINUM OBAT","MINUM PENAWAR"};
    if (pilihanP != LOGOUTP)
        printf("\n>>> %s\n\n", opsi[pilihanP]);
}

