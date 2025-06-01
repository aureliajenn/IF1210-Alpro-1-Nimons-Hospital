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
    while (user->kondisi.jumlahObat > 0) {
        printf("Inventory obat kamu:\n");
        tampilkanDaftarObat(user->kondisi.inventory, user->kondisi.jumlahObat);

        printf("Pilih obat untuk diminum (1 s.d %d, 0 untuk batal): ", user->kondisi.jumlahObat);
        int pilihan;
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid!\n");
            while (getchar() != '\n'); // bersihkan buffer
            continue;
        }

        if (pilihan == 0) {
            printf("Berhenti minum obat.\n");
            break;
        }

        if (pilihan < 1 || pilihan > user->kondisi.jumlahObat) {
            printf("Pilihan nomor tidak tersedia!\n");
            continue;
        }

        int idx = pilihan - 1;
        Obat obatTerpilih = user->kondisi.inventory[idx]; // salin sebelum dihapus

        // Hapus dari inventory
        for (int i = idx; i < user->kondisi.jumlahObat - 1; i++) {
            user->kondisi.inventory[i] = user->kondisi.inventory[i + 1];
        }
        user->kondisi.jumlahObat--;

        // Masukkan ke stack perut
        if (!pushObat(user, obatTerpilih.id, obatTerpilih.nama)) {
            printf("Gagal menyimpan obat ke perut!\n");
            return;
        }

        printf("\nGLEKGLEKGLEK... %s berhasil diminum!!!\n", obatTerpilih.nama);
    }

    if (user->kondisi.jumlahObat == 0) {
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
    printf("Obat %s berhasil ditambahkan ke inventory pasien %s\n",obatBaru.nama, user->identitas.username);
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

void minum_penawar(User* currentUser) {
    if (strcasecmp(currentUser->identitas.role, "pasien") != 0) {
        printf("Fitur ini hanya tersedia untuk pasien!\n");
        return;
    }

    // Cek apakah perut kosong
    if (currentUser->kondisi.perut.top == -1) {
        printf("Perut kosong!! Belum ada obat yang dimakan.\n");
        return;
    }

    // Keluarkan obat terakhir dari perut
    Obat keluar = currentUser->kondisi.perut.items[currentUser->kondisi.perut.top];
    currentUser->kondisi.perut.top--;

    // Masukkan ke inventory
    if (currentUser->kondisi.jumlahObat < MAX_OBAT) {
        currentUser->kondisi.inventory[currentUser->kondisi.jumlahObat] = keluar;
        currentUser->kondisi.jumlahObat++;
        printf("Uwekkk!!! %s keluar dan kembali ke inventory\n", keluar.nama);
    } else {
        printf("Inventory penuh! tidak bisa mengeluarkan obat\n", keluar.nama);
        currentUser->kondisi.perut.top++;
        currentUser->kondisi.perut.items[currentUser->kondisi.perut.top] = keluar;
    }
}
