#include "main.h"

#define MAX_OBAT 100

extern User *user;
extern Obat *obats;
extern int jumlah_obat;

void tampilkanDaftarObat(Obat inventory[], int jumlahObat) {
    printf("==================== DAFTAR OBAT =================\n");
    for (int i = 0; i < jumlahObat; i++) {
        printf("%d. %s\n", i + 1, inventory[i].nama);
    }
    printf("=================================================\n\n");
}

void lamanMinumObat() {
    if (user->kondisi.jumlahObat == 0) {
        printf("Inventory obat kamu kosong!\n");
        return;
    }

    tampilkanDaftarObat(user->kondisi.inventory, user->kondisi.jumlahObat);

    {printf("Pilih obat untuk diminum (1 s.d %d): ", user->kondisi.jumlahObat);}
    int pilihan;
    if (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }

    if (pilihan < 1 || pilihan > user->kondisi.jumlahObat) {
        printf("Pilihan nomor tidak tersedia!\n");
        return;
    }

    // for(int i=0;i<user->kondisi.jumlahObat;i++){printf("%d %s\n\n",i,user->kondisi.inventory[i].nama);}

    int idx = pilihan - 1;
    Obat *obatTerpilih = &user->kondisi.inventory[idx];

    if (!pushObat(user, obatTerpilih->id, obatTerpilih->nama)) {
        printf("Gagal menyimpan obat ke perut!\n");
        return;
    }

    for (int i = idx; i < user->kondisi.jumlahObat - 1; i++) {
        user->kondisi.inventory[i] = user->kondisi.inventory[i + 1];
    }
    user->kondisi.jumlahObat--;

    printf("\nGLEKGLEKGLEK... %s berhasil diminum!!!\n", obatTerpilih->nama);

    if (user->kondisi.jumlahObat > 0) {
        printf("\nSisa obat di inventory:\n");
        tampilkanDaftarObat(user->kondisi.inventory, user->kondisi.jumlahObat);
    } else {
        printf("\nInventory obat kamu sekarang kosong!\n");
    }
}

void tambahObatInventory(int idPasien, Obat obatBaru) {
    User *user = getUserById(idPasien);
    
    if (user == NULL) {
        fprintf(stderr, "Pasien dengan ID %d tidak ditemukan.\n", idPasien);
        return;
    }
    if (user->kondisi.jumlahObat >= MAX_OBAT) {
        fprintf(stderr, "Inventory penuh. Tidak bisa menambahkan obat lagi.\n");
        return;
    }

    user->kondisi.inventory[user->kondisi.jumlahObat++] = obatBaru;
}

void tambahObatDalamPerut(int idPasien, Obat obatBaru) {
    User *user = getUserById(idPasien);
    if (user == NULL) {
        fprintf(stderr, "Pasien dengan ID %d tidak ditemukan.\n", idPasien);
        return;
    }

    StackPerut *perut = &user->kondisi.perut;

    // Alokasi awal stack
    if (perut->items == NULL || perut->capacity == 0) {
        perut->capacity = 4;
        perut->items = malloc(perut->capacity * sizeof(Obat));
        if (perut->items == NULL) {
            perror("Gagal mengalokasikan memori untuk perut");
            exit(EXIT_FAILURE);
        }
        perut->top = -1; // stack kosong awal
    }

    // Perbesar kapasitas jika penuh
    if (perut->top + 1 >= perut->capacity) {
        perut->capacity *= 2;
        Obat *temp = realloc(perut->items, perut->capacity * sizeof(Obat));
        if (temp == NULL) {
            perror("Gagal memperluas kapasitas perut");
            exit(EXIT_FAILURE);
        }
        perut->items = temp;
    }

    // Push ke atas stack
    perut->items[++perut->top] = obatBaru;
}

Obat cariObatById(int id) {
    for (int i = 0; i < jumlah_obat; i++) {
        if (obats[i].id == id) {
            return obats[i];
        }
    }
    // Jika tidak ditemukan, return Obat kosong atau default
    Obat kosong = {0};
    strcpy(kosong.nama, "Obat Tidak Dikenal");
    return kosong;
}
