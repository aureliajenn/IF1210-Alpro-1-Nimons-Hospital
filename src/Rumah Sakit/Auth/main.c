// File main.c
#include "auth.h"

// Definisi Global
User *user = NULL;
User *users = NULL;
int jumlah_user = 0;
Pilihan pilihan;
PilihanPasien pilihanP;

int main(){
    user = (User *)malloc(sizeof(User));    // Alokasi pointer user
    if (user == NULL) {
        perror("Gagal mengalokasikan user");
        return 1;
    }

    users = (User *)malloc(MAX_USER * sizeof(User));    // Alokasi pointer users
    if (users == NULL){
        perror("Gagal membuat array");
        return 1;
    }

    // Konversi data user.csv ke arr dulu
    jumlah_user=0;
    ParseTarget pt = {users, &jumlah_user};
    CSVtoArr("../../../data/user.csv",handleUserRow,&pt);
    users = (User *)realloc(users, jumlah_user * sizeof(User));
    if (users == NULL){
        perror("gagal membuat array");
        return 1;
    }

    do {
        labelInput();

        switch(pilihan){
            case LOGIN: 
                login(); 
                break;
            case REGISTER: 
                registerpasien();
                break;
            case LUPAPASSWORD:
                lupaPassword();
                break;
        }

        if (user != NULL){
        if(strcmpi(user->identitas.role,"PASIEN")==0){lamanPasien();}
        else if(strcmpi(user->identitas.role,"MANAGER")==0){lamanManager();}
        else if(strcmpi(user->identitas.role,"DOKTER")==0){lamanDokter();}
        }

        switch(pilihanP){
            case DAFTARCHECKUP: 
                // blm 
                break;
            case ANTRIANSAYA: 
                // blm
                break;
            case MINUMOBAT: 
                // blm
                break;
            case MINUMPENAWAR: 
                // blm 
                break;
            case LOGOUT:
                logout();
                break;
        }

        if (pilihan != EXIT && pilihanP != LOGOUT) {
            printf("\nTekan Enter untuk kembali ke menu...");
            getchar(); getchar(); // pause
    } }while(pilihan != EXIT);

    clearScreen();

    char c;
    do{
        printf("\nApakah Anda mau melakukan penyimpanan file yang sudah diubah?(y/n)\n");
        scanf(" %c",&c);
        if(c=='y' || c=='Y'){
            ArrtoCSV("../../../data/user.csv",writeUsersToFile,NULL);
        }
    }while(c != 'y' && c != 'n' && c != 'Y' && c != 'N');
   
    clearScreen();
    
    printf("\nTerima kasih telah menggunakan sistem! <3\n\n");

    return 0;
}