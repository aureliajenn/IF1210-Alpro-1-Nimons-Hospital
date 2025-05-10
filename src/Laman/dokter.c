// #include "dokter.h"

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

void diagnosis(){
    extern Penyakit *penyakits;
    extern int jumlah_penyakit;


    //diagnosis penyakit
    int id_penyakit;
    for (int i = 0; i < jumlah_penyakit; i++){ //cek penyakit
        if (pasien->kondisi.suhu_tubuh > penyakits[i].suhu_tubuh_min && pasien->kondisi.suhu_tubuh < penyakits[i].suhu_tubuh_max) continue;
        if (pasien->kondisi.tekanan_darah_sistolik > penyakits[i].tekanan_darah_sistolik_min && pasien->kondisi.tekanan_darah_sistolik < penyakits[i].tekanan_darah_sistolik_max) continue;
        if (pasien->kondisi.tekanan_darah_diastolik > penyakits[i].tekanan_darah_diastolik_min && pasien->kondisi.tekanan_darah_diastolik < penyakits[i].tekanan_darah_diastolik_max) continue;
        if (pasien->kondisi.detak_jantung > penyakits[i].detak_jantung_min && pasien->kondisi.detak_jantung < penyakits[i].detak_jantung_max) continue;
        if (pasien->kondisi.saturasi_oksigen > penyakits[i].saturasi_oksigen_min && pasien->kondisi.saturasi_oksigen < penyakits[i].saturasi_oksigen_max) continue;
        if (pasien->kondisi.kadar_gula_darah > penyakits[i].kadar_gula_darah_min && pasien->kondisi.kadar_gula_darah < penyakits[i].kadar_gula_darah_max) continue;
        if (pasien->kondisi.berat_badan > penyakits[i].berat_badan_min && pasien->kondisi.berat_badan < penyakits[i].berat_badan_max) continue;
        if (pasien->kondisi.tinggi_badan > penyakits[i].tinggi_badan_min && pasien->kondisi.tinggi_badan < penyakits[i].tinggi_badan_max) continue;
        if (pasien->kondisi.kadar_kolesterol > penyakits[i].kadar_kolesterol_min && pasien->kondisi.kadar_kolesterol < penyakits[i].kadar_kolesterol_max) continue;
        if (pasien->kondisi.trombosit > penyakits[i].trombosit_min && pasien->kondisi.trombosit < penyakits[i].trombosit_max) continue;

        id_penyakit = penyakits[i].id;
        strcpy(pasien->identitas.riwayat_penyakit, penyakits[i].nama);
        printf("%s terdiagnosa penyakit %s!\n", pasien->identitas.username);
        return;
    }
    }
