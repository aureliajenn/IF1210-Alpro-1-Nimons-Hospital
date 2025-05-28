#ifndef MODEL_H
#define MODEL_H

#define MAX_USER 100
#define MAX_LINE_LEN 1024
#define MAX_FIELD 50
#define MAX_COL_LEN 100
#define MAX_OBAT 50

typedef enum
{
    LOGIN = 1,
    REGISTER,
    LUPAPASSWORD,
    EXIT
} Pilihan;

typedef enum
{
    DAFTARCHECKUP = 1,
    ANTRIANSAYA,
    MINUMOBAT,
    MINUMPENAWAR,
    DENAHRUMAHSAKIT,
    LOGOUTP
} PilihanPasien;

typedef enum
{
    DENAHRUMAHSAKITMANAGER = 1,
    LIHATUSER,
    CARIUSER,
    TAMBAHDOKTER,
    LOGOUTM,
} PilihanManager;

typedef enum
{
    DIAGNOSIS = 1,
    NGOBATIN,
    LOGOUTD
} PilihanDokter;

typedef struct
{
    int id;
    char username[MAX_LINE_LEN];
    char password[MAX_LINE_LEN];
    char role[MAX_LINE_LEN];
} Identitas;

typedef struct
{
    char riwayat_penyakit[MAX_LINE_LEN];
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

typedef struct
{
    Identitas identitas;
    KondisiPasien kondisi;
    Obat inventory[MAX_OBAT];
    int jumlahObat;
    StackPerut perut;
} User;

typedef struct
{
    int id;
    char nama[MAX_LINE_LEN];
    float suhu_tubuh_min;
    float suhu_tubuh_max;
    int tekanan_darah_sistolik_min;
    int tekanan_darah_sistolik_max;
    int tekanan_darah_diastolik_min;
    int tekanan_darah_diastolik_max;
    int detak_jantung_min;
    int detak_jantung_max;
    float saturasi_oksigen_min;
    float saturasi_oksigen_max;
    int kadar_gula_darah_min;
    int kadar_gula_darah_max;
    float berat_badan_min;
    float berat_badan_max;
    int tinggi_badan_min;
    int tinggi_badan_max;
    int kadar_kolesterol_min;
    int kadar_kolesterol_max;
    int trombosit_min;
    int trombosit_max;

} Penyakit;

typedef struct {
    int id;
    char nama[50];
} Obat;

typedef struct {
    Obat *items;
    int top;
    int capacity;
} StackPerut;

#endif