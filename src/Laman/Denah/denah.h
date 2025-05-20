#ifndef DENAH_H
#define DENAH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_ROOMS 20
#define MAX_PATIENTS 10

// Struktur untuk menyimpan informasi ruangan
typedef struct {
    int roomIndex;       // A1, A2, dll. (0-indexed)
    int doctorId;        // ID dokter
    int patientCount;    // Jumlah pasien
    int patients[MAX_PATIENTS]; // ID pasien
} Room;

// Struktur untuk menyimpan informasi obat pasien
typedef struct {
    int patientId;       // ID pasien
    int medicineCount;   // Jumlah obat
    int medicines[MAX_PATIENTS]; // ID obat
} PatientMedicine;

// Struktur untuk menyimpan informasi rumah sakit
typedef struct {
    int rows;            // Jumlah baris
    int cols;            // Jumlah kolom
    int maxPatientsPerRoom; // Maksimum pasien per ruangan
    Room rooms[MAX_ROOMS]; // Informasi ruangan
    int roomCount;       // Jumlah ruangan
    PatientMedicine medicines[MAX_PATIENTS]; // Informasi obat pasien
    int medicineCount;   // Jumlah informasi obat
} Hospital;

// Fungsi untuk mendapatkan label ruangan (A1, B2, dll.) dari indeks
void dapatkanLabelRuangan(int indeks, char *label, int kolom);

// Fungsi untuk memuat data rumah sakit dari file konfigurasi
int muatDataRumahSakit(const char *namaFile, Hospital *rumahSakit);

// Fungsi untuk menampilkan tata letak rumah sakit
void tampilkanDenahRumahSakit(Hospital *rumahSakit);

// Fungsi untuk menampilkan informasi detail ruangan
void tampilkanDetailRuangan(Hospital *rumahSakit);

// Fungsi untuk menampilkan inventaris obat
void tampilkanInventarisObat(Hospital *rumahSakit);

// Fungsi utama untuk menampilkan seluruh informasi rumah sakit
void tampilkanDenahRS(const char *fileKonfigurasi);

#endif // DENAH_H