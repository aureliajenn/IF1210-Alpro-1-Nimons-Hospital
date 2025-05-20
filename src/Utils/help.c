#include <stdio.h>
#include <string.h>

void help(const char role[], const char username[]) {
    printf("============= HELP =============\n\n");

    if (strcmp(role, "") == 0) {
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("1. LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("2. REGISTER: Membuat akun baru\n\n");
    } else if (strcmp(role, "Dokter") == 0) {
        printf("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", username);
        printf("1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
        printf("2. DIAGNOSIS: Melakukan diagnosis penyakit pasien berdasarkan kondisi tubuh pasien\n");
        printf("3. NGOBATIN: Memberi obat kepada pasien secara terurut\n\n");
    } else if (strcmp(role, "Pasien") == 0) {
        printf("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", username);
        printf("1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
        printf("2. DAFTAR_CHECKUP: Mendaftarkan diri untuk pemeriksaan dokter\n");
        printf("3. AKU_BOLEH_PULANG_GA_DOK: Melakukan pemeriksaan ulang kepada dokter untuk memastikan apakah pasien benar-benar sudah siap untuk pulang\n");
        printf("4. ANTRIAN_SAYA: Melihat status antrian\n");
        printf("5. MINUM_OBAT: Meminum obat yang telah diberikan oleh dokter\n");
        printf("6. MINUM_PENAWAR: Mengeluarkan obat terakhir yang diminum dan mengembalikannya ke dalam inventory obat\n\n");
    } else if (strcmp(role, "Manager") == 0) {
        printf("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", username);
        printf("1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
        printf("2. TAMBAH_DOKTER: Mendaftarkan dokter baru ke sistem\n");
        printf("3. LIHAT_USER: Melihat data seluruh pengguna (dokter dan pasien), atau secara spesifik hanya pasien atau hanya dokter\n");
        printf("4. CARI_USER: Mencari data pengguna secara spesifik berdasarkan ID atau Nama melalui perintah (CARI_USER), maupun secara lebih terfokus melalui (CARI_PASIEN) dan (CARI_DOKTER)\n");
        printf("5. LIHAT_ANTRIAN: Melihat rincian di seluruh ruangan saat ini. Ruangan yang perlu ditampilkan adalah ruangan yang tidak kosong\n\n");
    }

    printf("Footnote:\n");
    printf("1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("2. Jangan lupa untuk memasukkan input yang valid\n\n");
}