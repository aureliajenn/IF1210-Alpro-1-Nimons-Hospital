#ifndef DENAH_H
#define DENAH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_ROOMS 20
#define MAX_PATIENTS 10
#define MAX_MEDICINES 10
#define MAX_QUEUE 10

// Struktur untuk menyimpan informasi ruangan
typedef struct {
    int roomIndex;       // A1, A2, dll. (0-indexed)
    int doctorId;        // ID dokter (0 jika tidak ada dokter)
    int patientCount;    // Jumlah pasien di ruangan
    int patients[MAX_PATIENTS]; // ID pasien
    int queueCount;      // Jumlah pasien dalam antrian luar ruangan
    int queue[MAX_QUEUE];  // ID pasien dalam antrian luar
} Room;

// Struktur untuk menyimpan informasi obat pasien
typedef struct {
    int patientId;       // ID pasien
    int medicineCount;   // Jumlah obat
    int medicines[MAX_MEDICINES]; // ID obat
} PatientMedicine;

// Struktur untuk menyimpan informasi rumah sakit
typedef struct {
    int rows;            // Jumlah baris rumah sakit
    int cols;            // Jumlah kolom rumah sakit
    int maxPatientsPerRoom; // Maksimum pasien per ruangan
    int maxQueue;        // Maksimum pasien di luar ruangan
    Room rooms[MAX_ROOMS]; // Informasi ruangan
    int roomCount;       // Jumlah ruangan yang terisi
    PatientMedicine medicines[MAX_PATIENTS]; // Informasi obat yang dimiliki pasien
    int medicineCount;   // Jumlah informasi obat pasien
} Hospital;

// Fungsi untuk mendapatkan label ruangan (A1, A2, B1, B2, dll.)
void dapatkanLabelRuangan(int indeks, char *label, int kolom);

// Fungsi untuk memuat data rumah sakit dari file
int muatDataRumahSakit(const char *namaFile, Hospital *rumahSakit);

// Fungsi untuk menampilkan denah rumah sakit
void tampilkanDenahRumahSakit(Hospital *rumahSakit);

// Fungsi untuk menampilkan detail ruangan rumah sakit
void tampilkanDetailRuangan(Hospital *rumahSakit);

// Fungsi untuk menampilkan inventaris obat rumah sakit
void tampilkanInventarisObat(Hospital *rumahSakit);

// Fungsi untuk menampilkan denah rumah sakit dari file konfigurasi
void tampilkanDenahRS(const char *fileKonfigurasi);

#endif // DENAH_H