#include "main.h"

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

void labelDokter(){
    printf("1. Diagnosis\n");
    printf("2. Ngobatin\n");
    printf("3. Logout\n");
    printf("\n");
}

void labelMenuPasien(){
    printf("1. Daftar Check-Up\n");
    printf("2. Antrian Saya\n");
    printf("3. Minum Obat\n");
    printf("4. Minum Penawar\n");
    printf("5. Lihat Denah Rumah Sakit\n");
    printf("6. Pulang dok\n");
    printf("7. Logout\n");
    printf("\n");
}

void labelMenuManager(){
    printf("1. Lihat Denah Rumah Sakit\n");
    printf("2. Lihat User\n");
    printf("3. Cari User\n");
    printf("4. Tambah User Dokter\n");
    printf("5. Logout\n");
    printf("\n");
}

void labelMenuDokter(){
    printf("1. Diagnosis\n");
    printf("2. Ngobatin\n");
    printf("3. Logout\n");
    printf("\n");
}

void labelHelpBelumLogin(){
    printf("=========== HELP ===========\n");
    printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n");
    printf("LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
    printf("REGISTER: Membuat akun baru");
    printf("\n");
    printf("Footnote:\n");
    printf("Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("Jangan lupa untuk memasukkan input yang valid\n");
}

void labelHelpDokter(){
    extern User *user;
    printf("=========== HELP ===========\n");
    printf("Halo Dokter %s . Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:", user->identitas.username);
    printf("\n");
    printf("LOGOUT: Keluar dari akun yang sedang digunakan");
    printf("DIAGNOSIS: Melakukan diagnosis penyakit pasien berdasarkan kondisi tubuh pasien\n");
    printf("NGOBATIN: Memberi obat kepada pasien secara terurut");
    printf("\n");
    printf("Footnote:\n");
    printf("Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("Jangan lupa untuk memasukkan input yang valid\n");
}

void labelHelpPasien(){
    extern User *user;
    printf("=========== HELP ===========\n");
    printf("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n", user->identitas.username);
    printf("\n");
    printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
    printf("DAFTAR_CHECKUP: Mendaftarkan diri untuk pemeriksaan dokter\n");
    printf("AKU_BOLEH_PULANG_GA_DOK: Melakukan pemeriksaan ulang kepada dokter untuk memastikan apakah pasien benar-benar sudah siap untuk pulang\n");
    printf("ANTRIAN_SAYA: Melihat status antrian\n");
    printf("MINUM_OBAT: Meminum obat yang telah diberikan oleh dokter\n");
    printf("MINUM_PENAWAR: Mengeluarkan obat terakhir yang diminum dan mengembalikannya ke dalam inventory obat\n");
    printf("\n");
    printf("Footnote:\n");
    printf("Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("Jangan lupa untuk memasukkan input yang valid\n");
}

void labelHelpManager(){
    extern User *user;
    printf("=========== HELP ===========\n");
    printf("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n", user->identitas.username);
    printf("\n");
    printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
    printf("LIHAT_USER: Melihat data seluruh pengguna (dokter dan pasien), atau secara spesifik hanya pasien atau hanya dokter\n");
    printf("CARI_USER: Mencari data pengguna secara spesifik berdasarkan ID atau Nama melalui perintah (CARI_USER), maupun secara lebih terfokus melalui (CARI_PASIEN) dan (CARI_DOKTER)\n");
    printf("LIHAT_ANTRIAN: Melihat rincian di seluruh ruangan saat ini. Ruangan yang perlu ditampilkan adalah ruangan yang tidak kosong\n");
    printf("TAMBAH_DOKTER: Mendaftarkan dokter baru ke sistem\n");
    printf("\n");
    printf("Footnote:\n");
    printf("Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("Jangan lupa untuk memasukkan input yang valid\n");
}
