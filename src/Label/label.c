#include "label.h"

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
    printf("5. Lihat Denah Rumah Sakit\n");
    printf("6. Logout\n");
    printf("\n");
}

void labelMenuManager(){
    printf("1. Lihat Denah Rumah Sakit\n");
    printf("2. Lihat User\n");
    printf("3. Logout\n");
    printf("\n");
}

void labelMenuDokter(){
    printf("1. Diagnosis\n");
    printf("2. Ngobatin\n");
    printf("3. Logout\n");
    printf("\n");
}