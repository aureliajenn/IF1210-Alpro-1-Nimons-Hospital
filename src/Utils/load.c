#include "main.h"

// Deklarasi global dari main.c
extern User *users;
extern Penyakit *penyakits;
extern Map *map;
extern Hospital *rumahSakit;
extern Obat *obats;
extern ObatPenyakit *obat_penyakits;
extern int jumlah_user;
extern int jumlah_penyakit;
extern int jumlah_obat;
extern int jumlah_obat_penyakit;

#define MAX_LINE_LEN 256
#define MAX_OBAT 100

void load(const char *folder_name) {
    char userpath[MAX_LINE_LEN], penyakitpath[MAX_LINE_LEN], configpath[MAX_LINE_LEN], obatpath[MAX_LINE_LEN];

    sprintf(userpath, "data/%s/user.csv", folder_name);
    sprintf(penyakitpath, "data/%s/penyakit.csv", folder_name);
    sprintf(configpath, "data/%s/config.txt", folder_name);
    sprintf(obatpath, "data/%s/obat.csv", folder_name);
    
    // Cek apakah folder ada
    char folderpath[MAX_LINE_LEN];
    sprintf(folderpath, "data/%s", folder_name);

    struct stat st;
    if (stat(folderpath, &st) != 0 || !S_ISDIR(st.st_mode)) {
        printf("Folder \"%s\" tidak ditemukan di dalam folder data/.\n", folder_name);
        exit(1);
    }
    // Reset jumlah
    jumlah_user = 0;
    jumlah_penyakit = 0;
    jumlah_obat_penyakit = 0;

    ParseTarget pt = {users, &jumlah_user};
    ParsePenyakit pp = {penyakits, &jumlah_penyakit};
    ParseObat po = {obats,&jumlah_obat};
    ParseObatPenyakit pop = {obats,&jumlah_obat_penyakit};

    // Load file CSV ke array
    CSVtoArr(userpath, handleUserRow, &pt);
    CSVtoArr(penyakitpath, handlePenyakitRow, &pp);
    CSVtoArr(obatpath,handleObatRow, &po);

    if (jumlah_user > 0)
    {
        User *temp = realloc(users, jumlah_user * sizeof(User));
        if (temp)
            users = temp;
    }

    if (jumlah_penyakit > 0)
    {
        Penyakit *temp = realloc(penyakits, jumlah_penyakit * sizeof(Penyakit));
        if (temp)
            penyakits = temp;
    }

    if (jumlah_obat > 0)
    {
        Obat *temp = realloc(obats, jumlah_obat * sizeof(Obat));
        if (temp) obats = temp;
    }

    if (jumlah_obat_penyakit > 0)
    {
        ObatPenyakit *temp = realloc(obat_penyakits, jumlah_obat_penyakit * sizeof(ObatPenyakit));
        if (temp) obat_penyakits = temp;
    }

    loadConfig(configpath);
    // loadObat(obatpath);
    muatDataRumahSakit(configpath,rumahSakit);
}

User* getUserById(int id) {
    for (int i = 0; i < jumlah_user; i++) {
        if (users[i].identitas.id == id) {
            return &users[i];
        }
    }
    return NULL;
}

void loadConfig(const char *configPath) {
    FILE *file = fopen(configPath, "r");
    if (!file) {
        perror("Gagal membuka file config.txt");
        return;
    }

    char baris[MAX_LINE_LEN];
    int hitungBaris = 0;
    int totalRuangan = 0;
    int pasienInventoryCount = 0;
    int pasienPerutCount = 0;
    int mode = 0; // 0: ruangan, 1: inventory, 2: perut
    
    while (fgets(baris, MAX_LINE_LEN, file)) {
        baris[strcspn(baris, "\n")] = '\0';
        hitungBaris++;

        if (hitungBaris == 1) {
            int barisD = 0, kolomD = 0;
            parseDuaAngka(baris, &barisD, &kolomD);
            map = createMap(barisD * kolomD);
            map->rows = barisD;
            map->cols = kolomD;
            totalRuangan = barisD * kolomD;
        } else if (hitungBaris == 2) {
            int maxIn, maxOut;
            parseDuaAngka(baris, &maxIn, &maxOut);
            map->maxPasienDalamRuangan = maxIn;
            map->maxAntrianLuar = maxOut;
        } else if (hitungBaris >= 3 && hitungBaris < 3 + totalRuangan) {
            int nilai[100], count = parseAngka(baris, nilai);
            Dokter *dokter = malloc(sizeof(Dokter));
            dokter->ruangan = hitungBaris - 3;
            dokter->queue = createQueue();
            dokter->jumlahPasienDalamRuangan = 0;
            dokter->jumlahPasienLuarRuangan = 0;
            dokter->queueLength = 0;

            if (count == 0 || nilai[0] == 0) {
                dokter->id = 0;
                insertDoctor(map, dokter);
                continue;
            }

            dokter->id = nilai[0];
            for (int i = 1; i < count; i++) {
                if (nilai[i] == 0) continue;
                User *pasien = getUserById(nilai[i]);
                if (pasien == NULL) continue;

                User p;
                p.identitas.id = pasien->identitas.id;
                strcpy(p.identitas.username, pasien->identitas.username);
                p.kondisi.suhu_tubuh = pasien->kondisi.suhu_tubuh;
                p.kondisi.tekanan_darah_sistolik = pasien->kondisi.tekanan_darah_sistolik;
                p.kondisi.tekanan_darah_diastolik = pasien->kondisi.tekanan_darah_diastolik;
                p.kondisi.detak_jantung = pasien->kondisi.detak_jantung;
                p.kondisi.saturasi_oksigen = pasien->kondisi.saturasi_oksigen;
                p.kondisi.kadar_gula_darah = pasien->kondisi.kadar_gula_darah;
                p.kondisi.berat_badan = pasien->kondisi.berat_badan;
                p.kondisi.tinggi_badan = pasien->kondisi.tinggi_badan;
                p.kondisi.kadar_kolesterol = pasien->kondisi.kadar_kolesterol;
                p.kondisi.trombosit = pasien->kondisi.trombosit;

                enqueue(dokter->queue, p);
                if (dokter->jumlahPasienDalamRuangan < map->maxPasienDalamRuangan)
                    dokter->jumlahPasienDalamRuangan++;
                else
                    dokter->jumlahPasienLuarRuangan++;

                dokter->queueLength++;
            }
            insertDoctor(map, dokter);
        } else if (mode == 0) {
            pasienInventoryCount = convertStringToInt(baris);
            mode = 1;
        } else if (mode == 1 && pasienInventoryCount > 0) {
            int data[100];
            int count = parseAngka(baris, data);
            int idPasien = data[0];
            for (int i = 1; i < count; i++) {
                // printf("%d\n\n\n",data[i]);
                Obat obat = cariObatById(data[i]);
                // printf("%s\n\n\n",obat.nama);
                tambahObatInventory(idPasien, obat);
            }
            pasienInventoryCount--;
            if (pasienInventoryCount == 0)
                mode = 2;
        } else if (mode == 2) {
            pasienPerutCount = convertStringToInt(baris);
            mode = 3;
        } else if (mode == 3 && pasienPerutCount > 0) {
            int data[100];
            int count = parseAngka(baris, data);
            int idPasien = data[0];
            for (int i = 1; i < count; i++) {
                Obat obat = cariObatById(data[i]);
                tambahObatDalamPerut(idPasien, obat);
            }
            pasienPerutCount--;
        }
    }

    fclose(file);
}

// Helper untuk dua angka (dipisahkan spasi)
void parseDuaAngka(const char *str, int *a, int *b) {
    int i = 0, j = 0;
    char temp[10];

    while (str[i] >= '0' && str[i] <= '9') {
        temp[j++] = str[i++];
    }
    temp[j] = '\0';
    *a = convertStringToInt(temp);

    while (str[i] && (str[i] < '0' || str[i] > '9')) i++; // skip spasi

    j = 0;
    while (str[i] >= '0' && str[i] <= '9') {
        temp[j++] = str[i++];
    }
    temp[j] = '\0';
    *b = convertStringToInt(temp);
}

// Helper untuk parsing seluruh angka dalam 1 baris ke array
int parseAngka(const char *str, int *hasil) {
    int i = 0, j, count = 0;
    char temp[10];

    while (str[i] != '\0') {
        while (str[i] != '\0' && (str[i] < '0' || str[i] > '9')) i++;
        if (str[i] == '\0') break;

        j = 0;
        while (str[i] >= '0' && str[i] <= '9') {
            temp[j++] = str[i++];
        }
        temp[j] = '\0';
        hasil[count++] = convertStringToInt(temp);
    }

    return count;
}

// void loadObat(const char *filePath) {
//     FILE *file = fopen(filePath, "r");
//     if (!file) {
//         perror("Gagal membuka file obat.txt");
//         return;
//     }

//     char line[MAX_LINE_LEN];
//     int isFirstLine = 1;

//     while (fgets(line, MAX_LINE_LEN, file)) {
//         line[strcspn(line, "\n")] = '\0'; // hapus newline

//         if (isFirstLine) {
//             isFirstLine = 0; // skip header
//             continue;
//         }

//         int i = 0;
//         // Ambil ID
//         int id = 0;
//         while (line[i] >= '0' && line[i] <= '9') {
//             id = id * 10 + (line[i] - '0');
//             i++;
//         }

//         // Skip semicolon
//         if (line[i] != ';') continue;
//         i++;

//         // Ambil nama obat
//         char nama[50];
//         int j = 0;
//         while (line[i] != '\0' && j < 49) {
//             nama[j++] = line[i++];
//         }
//         nama[j] = '\0';

//         // Masukkan ke obats global
//         obats[jumlah_obat].id = id;
//         strncpy(obats[jumlah_obat].nama, nama, sizeof(obats[0].nama) - 1);
//         obats[jumlah_obat].nama[sizeof(obats[0].nama) - 1] = '\0';
//         jumlah_obat++;

//         if (jumlah_obat >= MAX_OBAT) break;
//     }

//     fclose(file);
// }

// void loadObatPenyakit(const char *filePath) {            //loader ObatPenyakit belum ada
// }
const char *getNamaObat(int id) {
    for (int i = 0; i < jumlah_obat; i++) {
        if (obats[i].id == id) {
            return obats[i].nama;
        }
    }
    return NULL;
}

void hapusElemenArray(int array[], int *length, int index) {
    if (index < 0 || index >= *length) {
        printf("Indeks tidak valid\n");
        return;
    }

    // Geser elemen ke kiri mulai dari index
    for (int i = index; i < *length - 1; i++) {
        array[i] = array[i + 1];
    }

    (*length)--; // Kurangi panjang array
}

void updateUsers(User user){
    for(int i=0 ; i < jumlah_user ; i++){
        if(user.identitas.id==users[i].identitas.id){
            users[i]=user;
            break;
        }
    }
}


int idTertinggi(){
    int highestId=0;
    for (int i=0;i<jumlah_user;i++){
        if(users[i].identitas.id>highestId) highestId = users[i].identitas.id;
    }
    return highestId;
}