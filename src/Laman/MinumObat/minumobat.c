#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minumobat.h"

extern User *user; 

void tampilkanDaftarObat(Obat inventory[], int jumlahObat) {
    printf("\n==================== DAFTAR OBAT =================\n");
    for (int i = 0; i < jumlahObat; i++) {
        printf("%d. %s\n", i + 1, inventory[i].nama);
    }
    printf("=================================================\n");
}

void lamanMinumObat() {
    if (strcmp(user->identitas.role, "pasien") != 0) {
        printf("Hanya pasien yang bisa menggunakan fitur ini!\n");
        return;
    }

    if (user->jumlahObat == 0) {
        printf("Inventory obat kamu kosong!\n");
        return;
    }

    Obat inventoryObat[user->jumlahObat];
    for (int i = 0; i < user->jumlahObat; i++) {
        inventoryObat[i].id = user->obat[i].id;
        strcpy(inventoryObat[i].nama, user->obat[i].nama);
    }
    tampilkanDaftarObat(inventoryObat, user->jumlahObat);
t
    printf("Pilih obat untuk diminum (1-%d): ", user->jumlahObat);
    int pilihan;
    if (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }

    if (pilihan < 1 || pilihan > user->jumlahObat) {
        printf("Pilihan nomor tidak tersedia!\n");
        return;
    }
    int idx = pilihan - 1;

    if (!pushObat(user, inventoryObat[idx].id, inventoryObat[idx].nama)) {
        printf("Gagal menyimpan obat ke perut!\n");
        return;
    }

    for (int i = idx; i < user->jumlahObat - 1; i++) {
        user->obat[i] = user->obat[i + 1];
    }
    user->jumlahObat--;
    printf("\nGLEKGLEKGLEK... %s berhasil diminum!!!\n", inventoryObat[idx].nama);

    if (user->jumlahObat > 0) {
        printf("\nSisa obat di inventory:\n");
        tampilkanDaftarObat(user->obat, user->jumlahObat);
    } else {
        printf("\nInventory obat kamu sekarang kosong!\n");
    }
}