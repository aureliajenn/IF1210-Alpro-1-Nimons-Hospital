// File main.c
#include "src/Model/model.h"
#include "src/Label/label.h"
#include "src/DataParser/dataParser.h"
#include "src/Laman/pasien.h"
#include "src/Laman/dokter.h"
#include "src/Laman/manager.h"
#include "src/Utils/save.h"
#include "src/Utils/load.h"

// Prosedur Lokal
void labelInput();

// Definisi Global
User *user = NULL;
User *users = NULL;
Penyakit *penyakits = NULL;

int jumlah_user = 0;
int jumlah_penyakit = 0;

Pilihan pilihan;
PilihanPasien pilihanP;
PilihanDokter pilihanD;

int main(int argc, char *argv[]) {
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

    penyakits = (Penyakit *)malloc(MAX_USER * sizeof(Penyakit));    // Alokasi pointer users
    if (penyakits == NULL){
        perror("Gagal membuat array");
        return 1;
    }

    if (argc < 2) {
        printf("Tidak ada nama folder yang diberikan!\n");
        printf("Usage : ./main <<nama_folder>>\n");
        return 1;
    }

    const char *folder = argv[1];
    load(folder);
    printf("Selamat datang kembali di rumah sakit K01-N !\n\n");

    // Konversi data user.csv ke arr dulu
    jumlah_user=0;  jumlah_penyakit = 0;
    ParseTarget pt = {users, &jumlah_user};
    ParsePenyakit pp = {penyakits, &jumlah_penyakit};
    
    char user_path[256], penyakit_path[256];
    snprintf(user_path, sizeof(user_path), "data/%s/user.csv", folder);
    snprintf(penyakit_path, sizeof(penyakit_path), "data/%s/penyakit.csv", folder);

    CSVtoArr(user_path, handleUserRow, &pt);
    CSVtoArr(penyakit_path, handlePenyakitRow, &pp);

    if (jumlah_user > 0) {
    User *temp = realloc(users, jumlah_user * sizeof(User));
    if (temp == NULL){
        perror("gagal membuat array");
        free(users);
        return 1;
    }
    users = temp;
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
        if(strcasecmp(user->identitas.role,"PASIEN")==0){lamanPasien();}
        else if(strcasecmp(user->identitas.role,"MANAGER")==0){
            // lamanManager();
        }
        else if(strcasecmp(user->identitas.role,"DOKTER")==0){
            // lamanDokter();
        }
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
            case DENAHRUMAHSAKIT: 
                // blm 
                break;
            case LOGOUTP:
                logout();
                break;
        }

        switch(pilihanD){
            case DIAGNOSIS:
                //blm
                break;
            case NGOBATIN:
                //blm
                break;
            case LOGOUTD:
                logout();
                break;
        }

        if (pilihan != EXIT && pilihanP != LOGOUTP && pilihanD != LOGOUTD) {
            printf("\nTekan Enter untuk kembali ke menu...");
            getchar(); getchar(); // pause
    } }while(pilihan != EXIT);

    clearScreen();
    
    char c;
    do{
        printf("\nApakah Anda mau melakukan penyimpanan file yang sudah diubah?(y/n)\n");
        scanf(" %c",&c);
        if(c=='y' || c=='Y'){
            char folder_name[MAX_LINE_LEN];
            printf("Masukkan nama folder penyimpanan (misal: RSMitraKasih): ");
            scanf("%99s", folder_name);
            save(folder_name);  // panggil prosedur save
        }
    }while(c != 'y' && c != 'n' && c != 'Y' && c != 'N');
   
    // clearScreen();
    
    printf("\nTerima kasih telah menggunakan sistem! <3\n\n");

    return 0;
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
