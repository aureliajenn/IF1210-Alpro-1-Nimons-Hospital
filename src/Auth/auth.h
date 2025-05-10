// File auth.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../DataParser/dataParser.h"

#ifndef AUTH_H
#define AUTH_H

typedef enum{
    LOGIN=1,
    REGISTER,
    LUPAPASSWORD,
    EXIT
} Pilihan;

typedef enum{
    DAFTARCHECKUP=1,
    ANTRIANSAYA,
    MINUMOBAT,
    MINUMPENAWAR,
    LOGOUTP
} PilihanPasien;

typedef enum{
    DIAGNOSIS = 1,
    NGOBATIN,
    LOGOUTD
 } PilihanDokter;

#define MAX_USER 100
#define MAX_LINE_LEN 1024
#define MAX_FIELD 50
#define MAX_COL_LEN 100


typedef struct {
    int id;
    char username[MAX_LINE_LEN];
    char password[MAX_LINE_LEN];
    char role[MAX_LINE_LEN];
    char riwayat_penyakit[MAX_LINE_LEN];
    
} Identitas;

typedef struct {
    float suhu_tubuh;
    int tekanan_darah_sistolik;
    int tekanan_darah_diastolik;
    int detak_jantung;
    float saturasi_oksigen;
    int kadar_gula_darah;
    float berat_badan;
    int tinggi_badan;
    int kadar_kolesterol;
    int kadar_kolesterol_ldl;
    int trombosit;

} KondisiPasien;

typedef struct {
    Identitas identitas;
    KondisiPasien kondisi;
} User;

typedef struct {
    User *arr;
    int *jumlah;
} ParseTarget;

void clearScreen();

void labelRS();
// Menampilkan label besar "RS K01-N" sebagai user interface

void labelUser();
// Menampilkan label besar "<Role> <Username>" sebagai user interface

void labelMenu();
// Menampilkan user interface menu awal

void labelMenuPasien();
// Menampilkan user interface menu untuk pasien

void labelMenuDokter();
// Menampilkan user interface menu untuk dokter

void labelMenuManager();
// Menampilkan user interface menu untuk manager

void labelInput();
// Menampilkan menu dan input sebagai UI utama

void login();
// Procedure untuk login

void logout();
// Procedure untuk logout

void registerpasien();
// Procedure untuk register pasien

void lupaPassword();
// Procedur untuk user yang lupa password

void lamanPasien();
// Halaman untuk pasien yang berhasil masuk ke akun

void lamanDokter();
// Halaman untuk dokter yang berhasil masuk ke akun

void lamanManager();
// Halaman untuk manager yang berhasil masuk ke akun

#endif