#include "main.h"

void resetKondisiPasien(User *pasien) {
    // Reset semua atribut di kondisi pasien ke nilai default

    pasien->kondisi.riwayat_penyakit[0] = '\0';
    pasien->kondisi.suhu_tubuh = 0.0f;
    pasien->kondisi.tekanan_darah_sistolik = 0;
    pasien->kondisi.tekanan_darah_diastolik = 0;
    pasien->kondisi.detak_jantung = 0;
    pasien->kondisi.saturasi_oksigen = 0.0f;
    pasien->kondisi.kadar_gula_darah = 0;
    pasien->kondisi.berat_badan = 0.0f;
    pasien->kondisi.tinggi_badan = 0;
    pasien->kondisi.kadar_kolesterol = 0;
    pasien->kondisi.trombosit = 0;

    // Reset inventory obat
    pasien->kondisi.jumlahObat = 0;
    for (int i = 0; i < MAX_OBAT; i++) {
        pasien->kondisi.inventory[i].id = 0;
        pasien->kondisi.inventory[i].nama[0] = '\0';
    }

    // Reset StackPerut (tumpukan obat yang sudah diminum)
    pasien->kondisi.perut.top = -1;
    if (pasien->kondisi.perut.items != NULL) {
        for (int i = 0; i <= pasien->kondisi.perut.top; i++) {
            pasien->kondisi.perut.items[i].id = 0;
            pasien->kondisi.perut.items[i].nama[0] = '\0';
        }
    }

    pasien->kondisi.sudahDiagnosis = 0;
    pasien->kondisi.sudahDiobati = 0;
}

int cekUrutanObat(User *pasien, ObatPenyakit *obat_penyakits, int jumlah_obat_penyakit) {
    if (pasien->kondisi.perut.top + 1 != jumlah_obat_penyakit) return 0;
    for (int i = 0; i <= pasien->kondisi.perut.top; ++i) {
        if (pasien->kondisi.perut.items[i].id != obat_penyakits[i].obat_id) {
            return 0;
        }
    }
    return 1;
}

void pulangDok() {
    extern User *users;
    extern User *user;
    extern int jumlah_user;
    extern ObatPenyakit *obat_penyakits;
    extern int jumlah_obat_penyakit;
    extern Map *map;

    if (!user->kondisi.sudahDiagnosis) {
        printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");
        return;
    }

    if (!user->kondisi.sudahDiobati) {
        printf("Kamu belum diobati dokter, jangan buru-buru pulang!\n");
        return;
    }
    
    if (user->kondisi.jumlahObat != 0) {
        printf("Dokter sedang memeriksa keadaanmu... \n\n");
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
        return;
    }

    // --- Filter dan urutkan obat sesuai penyakit pasien ---
    ObatPenyakit urutanObat[50];
    int idP = getPenyakitIdByPenyakitName(user->kondisi.riwayat_penyakit);
    if (idP == -1) { // penyakit tidak ditemukan
        printf("Kamu sudah didiagnosis, tapi tidak ditemukan penyakit yang perlu obat.\n");
        printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");
        resetKondisiPasien(user);
        return;
    }
    int jmlObatResep = filterObatByPenyakit(obat_penyakits, jumlah_obat_penyakit, idP , urutanObat, 50);

    printf("Dokter sedang memeriksa keadaanmu... \n\n");

    // --- cek urutan minum obat pasien ---
    if (!cekUrutanObat(user, urutanObat, jmlObatResep)) {
        printf("Maaf, tapi kamu masih belum bisa pulang!\n\n");

        printf("Urutan peminuman obat yang diharapkan:\n");
        for (int i = 0; i < jmlObatResep; ++i) {
            // Ganti dengan nama obat dari obat_id, misal:
            printf("%s", getNamaObat(urutanObat[i].obat_id));
            if (i < jmlObatResep - 1) printf(" -> ");
        }
        printf("\n\nUrutan obat yang kamu minum:\n");
        for (int i = 0; i <= user->kondisi.perut.top; ++i) {
            printf("%s", user->kondisi.perut.items[i].nama);
            if (i < user->kondisi.perut.top) printf(" -> ");
        }
        printf("\n\nSilahkan kunjungi dokter untuk meminta penawar yang sesuai !\n");
        return;
    }

    printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");
    resetKondisiPasien(user);
    extern int isLoggedIn;
    extern int pilihanP;
    logout();
    isLoggedIn = 0;
    pilihanP = 0;
}

// Fungsi pembanding untuk qsort berdasarkan urutan_minum
int compareObatPenyakit(const void *a, const void *b) {
    ObatPenyakit *op1 = (ObatPenyakit *)a;
    ObatPenyakit *op2 = (ObatPenyakit *)b;
    return op1->urutan_minum - op2->urutan_minum;
}

// Filter dan sortir obat untuk penyakit tertentu
// hasil disimpan di output[], maksimal maxOutput
// return jumlah obat yang sesuai penyakit tersebut
int filterObatByPenyakit(ObatPenyakit *data, int dataCount, int penyakitId, ObatPenyakit *output, int maxOutput) {
    int j = 0;
    for (int i = 0; i < dataCount; i++) {
        if (data[i].penyakit_id == penyakitId) {
            if (j < maxOutput) {
                output[j++] = data[i];
            } else {
                break;
            }
        }
    }
    // sortir berdasarkan urutan_minum
    qsort(output, j, sizeof(ObatPenyakit), compareObatPenyakit);

    return j;
}

int getPenyakitIdByPenyakitName(const char *namaPenyakit) {
    extern Penyakit *penyakits;
    extern int jumlah_penyakit;
    for (int i = 0; i < jumlah_penyakit; i++) {
        if (strcmp(penyakits[i].nama, namaPenyakit) == 0) {
            return penyakits[i].id;
        }
    }
    return -1; // Tidak ditemukan
}
