#ifndef DENAH_H
#define DENAH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Model/model.h"

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

const char *dapatkanUsername(User *users, int userCount, int id, const char *role);

void dapatkanLabelRuangan(int index, char *labelRuangan, int cols);

int muatDataRumahSakit(const char *namaFile, Hospital *rumahSakit);

void tampilkanDenahRumahSakit(Hospital *rumahSakit);

void tampilkanDetailRuangan(Hospital *rumahSakit, char *kodeRuangan, User *users, int userCount);

void tampilkanInventarisObat(Hospital *rumahSakit);

#endif