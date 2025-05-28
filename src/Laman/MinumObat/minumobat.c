#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minumobat.h"
#include "../../ADT/stack.h"

extern User *user; 

typedef struct {
    int id;
    char nama[50];
} Obat;

// Fungsi helper untuk menampilkan daftar obat
void tampilkanDaftarObat(Obat inventory[], int jumlahObat) {
    printf("\n==================== DAFTAR OBAT =================\n");
    for (int i = 0; i < jumlahObat; i++) {
        printf("%d. %s\n", i + 1, inventory[i].nama);
    }
    printf("=================================================\n");
}

void lamanMinumObat() {
    // Validasi user harus pasien
    if (strcmp(user->identitas.role, "pasien") != 0) {
        printf("Hanya pasien yang bisa menggunakan fitur ini!\n");
        return;
    }

    // Validasi pasien memiliki obat di inventory
    if (user->jumlahObat == 0) {
        printf("Inventory obat kamu kosong!\n");
        return;
    }

    // Konversi data obat ke array untuk ditampilkan
    Obat inventoryObat[user->jumlahObat];
    for (int i = 0; i < user->jumlahObat; i++) {
        inventoryObat[i].id = user->obat[i].id;
        strcpy(inventoryObat[i].nama, user->obat[i].nama);
    }

    // Menampilkan daftar obat
    tampilkanDaftarObat(inventoryObat, user->jumlahObat);

    // Meminta input pilihan obat
    printf("Pilih obat untuk diminum (1-%d): ", user->jumlahObat);
    int pilihan;
    if (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }

    // Validasi pilihan
    if (pilihan < 1 || pilihan > user->jumlahObat) {
        printf("Pilihan nomor tidak tersedia!\n");
        return;
    }

    // Indeks array dimulai dari 0
    int index = pilihan - 1;

    // Simpan obat yang akan diminum ke perut (stack)
    if (!pushToPerut(user, inventoryObat[index].id, inventoryObat[index].nama)) {
        printf("Gagal menyimpan obat ke perut!\n");
        return;
    }

    // Hapus obat dari inventory
    for (int i = index; i < user->jumlahObat - 1; i++) {
        user->obat[i] = user->obat[i + 1];
    }
    user->jumlahObat--;

    // Tampilkan efek minum obat
    printf("\nGLEKGLEKGLEK... %s berhasil diminum!!!\n", inventoryObat[index].nama);

    // Tampilkan sisa obat jika masih ada
    if (user->jumlahObat > 0) {
        printf("\nSisa obat di inventory:\n");
        tampilkanDaftarObat(user->obat, user->jumlahObat);
    } else {
        printf("\nInventory obat kamu sekarang kosong!\n");
    }
}