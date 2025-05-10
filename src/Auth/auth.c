// File auth.c
#include "auth.h"
#include <strings.h>

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void labelRS(){
    printf("=====================================\n");
    printf("           RUMAH SAKIT K01-N         \n");
    printf("=====================================\n");
}

void labelUser(){
    extern User *user;
    printf("=====================================\n");
    printf("           %s %s      \n",user->identitas.role,user->identitas.username);
    printf("=====================================\n");
}

void labelMenu(){
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. LupaPassword\n");
    printf("4. Exit\n");
    printf("\n");
}

void labelMenuPasien(){
    printf("1. Daftar Check-Up\n");
    printf("2. Antrian Saya\n");
    printf("3. Minum Obat\n");
    printf("4. Minum Penawar\n");
    printf("5. Logout\n");
    printf("\n");
}

void labelMenuDokter(){
    printf("1. Diagnosis\n");
    printf("2. Ngobatin\n");
    printf("3. Logout\n");
    printf("\n");
}

void labelInput(){
    extern Pilihan pilihan;
    int input;
    int valid = 0;

    while (!valid) {
        clearScreen();
        labelRS();
        labelMenu();
        printf(">>> Masukkan pilihan (1-4): ");
        scanf("%d", &input);
        if (input != 1 && input != 2 && input != 3 && input != 4){
            // input bukan angka
            while(getchar() != '\n'); // flush input buffer
            printf("\nInput tidak valid! Masukkan angka antara 1-4.");
            printf("\nSilahkan enter untuk mengulang!\n");
            getchar(); // tunggu enter
            continue;
        }

        switch (input) {
            case 1: case 2: case 3:
                pilihan = input;
                valid = 1;
                break;
            case 4:
                pilihan = EXIT;
                valid = 1;
                break;
            default:
                printf("\nPilihan tidak valid! Silakan ulangi.\n");
                getchar(); // tunggu enter
        }
    }

    char *opsi[] = {"", "LOGIN", "REGISTER", "LUPA PASSWORD"};
    if (pilihan != EXIT)
        printf("\n>>> %s\n\n", opsi[pilihan]);
}

void login(){
    extern User *user; 
    extern User *users;
    extern int jumlah_user;
    int valid=0,format;
    char nama[50],role[50];

    clearScreen();
    do{
        format=1;
        printf("Username: ");
        scanf("%s", user->identitas.username);
        for (int i = 0; user->identitas.username[i] != '\0'; i++) {
            char c = user->identitas.username[i];
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))){
                format = 0;
                printf("Format username hanya boleh huruf! Ulangi\n");
                break;
            }
        }
        }while(!format);

    strcpy(nama,user->identitas.username);
    printf("Password: ");
    scanf("%s", user->identitas.password);
    for (int i = 0; i < jumlah_user; i++) {
        if (strcmpi(users[i].identitas.username, user->identitas.username) == 0) {
            if (strcmp(users[i].identitas.password, user->identitas.password) == 0) {
            valid = 1; 
            strcpy(role,users[i].identitas.role);
            strcpy(user->identitas.role,role);
            break;
            }else{
                printf("\nUsername atau password salah untuk pengguna yang bernama %s!\n\n",nama);
                valid = -1;
            }
        }
    }

    if (!valid) {
        printf("\nTidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n\n",nama);
    }
    else if(valid==1)
    {
    printf("\nSelamat pagi %s %s! \n\n",role,nama);}
}

void logout(){
    extern User *user;
    if (user != NULL) {
        free(user);     
        user = NULL;    
    }
}

void registerpasien(){
    extern User *user;
    extern User *users;
    extern int jumlah_user;
    int format,valid=1;
    
    clearScreen();
    do{
    format=1;
    printf("Username: ");
    scanf("%s", user->identitas.username);
    for (int i = 0; user->identitas.username[i] != '\0'; i++) {
        char c = user->identitas.username[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))){
            format = 0;
            printf("Format username hanya boleh huruf! Ulangi\n");
            break;
        }
    }
    }while(!format);

    for(int i=0;i<jumlah_user;i++){
        if(strcmpi((users)[i].identitas.username,user->identitas.username)==0){
            valid=0;
        }
    }

    if(!valid){
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.",user->identitas.username);
    }else{
        users = (User *)realloc(users,(jumlah_user+1) * sizeof(User));
        if(users==NULL){
            perror("gagal membuat array");
            exit(1);
        }else{
            printf("Password: ");
            scanf("%s", user->identitas.password);
            strcpy((users)[jumlah_user].identitas.username,user->identitas.username);
            strcpy((users)[jumlah_user].identitas.password,user->identitas.password);
            strcpy((users)[jumlah_user].identitas.role,"pasien");
            jumlah_user++;
            printf("Pasien %s berhasil ditambahkan!\n",user->identitas.username);
        }
    }
}

void lupaPassword(){
    extern User *user;
    extern User *users;
    extern int jumlah_user;
    int format,idx,valid=0;
    char kodeUnik[MAX_LINE_LEN],pass[MAX_LINE_LEN];

        do{
            format=1;
            printf("Username: ");
            scanf("%s", user->identitas.username);
            for (int i = 0; user->identitas.username[i] != '\0'; i++) {
                char c = user->identitas.username[i];
                if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))){
                    format = 0;
                    printf("Format username hanya boleh huruf! Ulangi\n");
                    break;
                }
            }
        }while(!format);

        for(int i=0;i<jumlah_user;i++){
            if(strcmpi((users)[i].identitas.username,user->identitas.username)==0){
                valid=1; idx=i;
            }
        }

        if(!valid){
            printf("Username tidak terdaftar!\n");
        }else{
        printf("Kode Unik: ");
        scanf("%s", kodeUnik);
        int i = 0, p = 0;
        while (kodeUnik[i] != '\0') {
            char c = kodeUnik[i];
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                i++; // pindah ke angka
                char count[10]; int k = 0;
                while (kodeUnik[i] >= '0' && kodeUnik[i] <= '9') {
                    count[k++] = kodeUnik[i++];
                }
                count[k] = '\0'; // Terminasi
         
                int result = 0;
                for (int j = 0; count[j] != '\0'; j++) {
                    result = result * 10 + (count[j] - '0');
                }
        
                for (int r = 0; r < result; r++) {
                    pass[p++] = c;
                }
            } else {
                i++; // skip karakter aneh
            }
        }
        pass[p] = '\0'; // Terminasi

        if(strcmpi(user->identitas.password,pass)==0){
            printf("Halo Dokter %s, silakan daftarkan ulang password anda!\n",user->identitas.username);
            printf("Password baru: ");
            scanf("%s",&(users)[idx].identitas.password);
            printf("Berhasil!\n");
        }else{
            printf("Kode unik salah!\n");
        }
        }
}

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
        scanf("%d", &input);
        if (input != 1 && input != 2 && input != 3 && input != 4 && input != 5){
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
                pilihanP = LOGOUT;
                valid = 1;
                break;
            default:
                printf("\nPilihan tidak valid! Silakan ulangi.\n");
                getchar(); // tunggu enter
        }
    }

    char *opsi[] = {"", "DAFTAR CHECK-UP", "ANTRIAN SAYA", "MINUM OBAT","MINUM PENAWAR"};
    if (pilihanP != LOGOUT)
        printf("\n>>> %s\n\n", opsi[pilihanP]);
}

void lamanManager(){

}

void lamanDokter(){

}

