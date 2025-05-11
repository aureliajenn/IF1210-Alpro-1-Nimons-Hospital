// File auth.c
#include "auth.h"

void cekFormatUsn(int *format, User *user){
    do{
        *format=1;
        printf("Username: ");
        scanf("%s", user->identitas.username);
        for (int i = 0; user->identitas.username[i] != '\0'; i++) {
            char c = user->identitas.username[i];
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))){
                *format = 0;
                printf("Format username hanya boleh huruf! Ulangi\n");
                break;
            }
        }
        }while(!*format);
}

void login(){
    extern User *user; 
    extern User *users;
    extern int jumlah_user;
    int valid=0,format;
    char nama[MAX_LINE_LEN],role[MAX_LINE_LEN];

    clearScreen();

    cekFormatUsn(&format,user);

    strcpy(nama,user->identitas.username);
    printf("Password: ");
    scanf("%s", user->identitas.password);
    for (int i = 0; i < jumlah_user; i++) {
        if (strcasecmp(users[i].identitas.username, user->identitas.username) == 0) {
            if (strcasecmp(users[i].identitas.password, user->identitas.password) == 0) {
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

    cekFormatUsn(&format,user);

    for(int i=0;i<jumlah_user;i++){
        if(strcasecmp((users)[i].identitas.username,user->identitas.username)==0){
            valid=0;
        }
    }

    if(!valid){
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.",user->identitas.username);
        free(user);
        user = NULL;
        return;  // Kembali agar tidak lanjut
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

    cekFormatUsn(&format,user);
    
    for(int i=0;i<jumlah_user;i++){
        if(strcasecmp((users)[i].identitas.username,user->identitas.username)==0){
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
    if(strcasecmp(user->identitas.password,pass)==0){
        printf("Halo Dokter %s, silakan daftarkan ulang password anda!\n",user->identitas.username);
        printf("Password baru: ");
        scanf("%s",&(users)[idx].identitas.password);
        printf("Berhasil!\n");
    }else{
        printf("Kode unik salah!\n");
    }
    }
}
