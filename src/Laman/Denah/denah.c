#include "Denah.h"

void dapatkanLabelRuangan(int indeks, char *label, int kolom) {
    char baris = 'A' + (indeks / kolom);
    int kol = (indeks % kolom) + 1;
    sprintf(label, "%c%d", baris, kol);
}

int muatDataRumahSakit(const char *namaFile, Hospital *rumahSakit) {
    FILE *file = fopen(namaFile, "r");
    if (file == NULL) {
        printf("Error: Gagal membuka file %s\n", namaFile);
        return 0;
    }

    char baris[MAX_LINE_LENGTH];
    int hitungBaris = 0;
    
    rumahSakit->roomCount = 0;
    rumahSakit->medicineCount = 0;
    
    while (fgets(baris, MAX_LINE_LENGTH, file)) {
        baris[strcspn(baris, "\n")] = 0;
        
        hitungBaris++;
        
        if (hitungBaris == 1) {
            sscanf(baris, "%d %d", &rumahSakit->rows, &rumahSakit->cols);
        } else if (hitungBaris == 2) {
            sscanf(baris, "%d", &rumahSakit->maxPatientsPerRoom);
        } else if (hitungBaris <= 8) {
            int nilai[MAX_PATIENTS + 1]; 
            char *token = strtok(baris, " ");
            int hitungNilai = 0;
            
            while (token != NULL && hitungNilai < MAX_PATIENTS + 1) {
                nilai[hitungNilai++] = atoi(token);
                token = strtok(NULL, " ");
            }
            
            if (hitungNilai >= 1) {
                Room *ruangan = &rumahSakit->rooms[rumahSakit->roomCount];
                ruangan->roomIndex = hitungBaris - 3;
                ruangan->doctorId = nilai[0];
                ruangan->patientCount = hitungNilai - 1;
                
                for (int i = 0; i < ruangan->patientCount; i++) {
                    ruangan->patients[i] = nilai[i + 1];
                }
                
                rumahSakit->roomCount++;
            }
        } else {
            int nilai[MAX_PATIENTS];
            char *token = strtok(baris, " ");
            int hitungNilai = 0;
            
            while (token != NULL && hitungNilai < MAX_PATIENTS) {
                nilai[hitungNilai++] = atoi(token);
                token = strtok(NULL, " ");
            }
            
            if (hitungNilai >= 1) {
                PatientMedicine *obat = &rumahSakit->medicines[rumahSakit->medicineCount];
                obat->patientId = nilai[0];
                obat->medicineCount = hitungNilai - 1;
                
                for (int i = 0; i < obat->medicineCount; i++) {
                    obat->medicines[i] = nilai[i + 1];
                }
                
                rumahSakit->medicineCount++;
            }
        }
    }
    
    fclose(file);
    return 1;
}

void tampilkanDenahRumahSakit(Hospital *rumahSakit) {
    printf("\n");
    for (int j = 1; j <= rumahSakit->cols; j++) {
        printf("%-7d", j);
    }
    printf("\n");

    for (int j = 0; j < rumahSakit->cols; j++) {
        printf("+-------");
    }
    printf("+\n");
    
    for (int i = 0; i < rumahSakit->rows; i++) {
        for (int j = 0; j < rumahSakit->cols; j++) {
            int indeksRuangan = i * rumahSakit->cols + j;
            char labelRuangan[5];
            dapatkanLabelRuangan(indeksRuangan, labelRuangan, rumahSakit->cols);
            printf("| %-5s ", labelRuangan);
        }
        printf("|\n");
        
        for (int j = 0; j < rumahSakit->cols; j++) {
            printf("+-------");
        }
        printf("+\n");
    }
}

void tampilkanDetailRuangan(Hospital *rumahSakit) {
    printf("\nDetail Ruangan:\n");
    for (int i = 0; i < rumahSakit->roomCount; i++) {
        char labelRuangan[5];
        dapatkanLabelRuangan(rumahSakit->rooms[i].roomIndex, labelRuangan, rumahSakit->cols);
        
        printf("Ruangan %s: ", labelRuangan);
        
        if (rumahSakit->rooms[i].doctorId == 0) {
            printf("Tidak ada dokter, ");
        } else {
            printf("Dokter ID %d, ", rumahSakit->rooms[i].doctorId);
        }
        
        if (rumahSakit->rooms[i].patientCount == 0) {
            printf("Tidak ada pasien\n");
        } else {
            printf("Pasien: ");
            for (int j = 0; j < rumahSakit->rooms[i].patientCount; j++) {
                printf("%d", rumahSakit->rooms[i].patients[j]);
                if (j < rumahSakit->rooms[i].patientCount - 1) {
                    printf(", ");
                }
            }
            printf("\n");
        }
    }
}

void tampilkanInventarisObat(Hospital *rumahSakit) {
    printf("\nInventaris Obat Pasien:\n");
    for (int i = 0; i < rumahSakit->medicineCount; i++) {
        printf("Pasien ID %d: ", rumahSakit->medicines[i].patientId);
        if (rumahSakit->medicines[i].medicineCount == 0) {
            printf("Tidak ada obat\n");
        } else {
            printf("Obat: ");
            for (int j = 0; j < rumahSakit->medicines[i].medicineCount; j++) {
                printf("%d", rumahSakit->medicines[i].medicines[j]);
                if (j < rumahSakit->medicines[i].medicineCount - 1) {
                    printf(", ");
                }
            }
            printf("\n");
        }
    }
}

void tampilkanDenahRS(const char *fileKonfigurasi) {
    Hospital rumahSakit;
    
    if (muatDataRumahSakit(fileKonfigurasi, &rumahSakit)) {
        tampilkanDenahRumahSakit(&rumahSakit);
        tampilkanDetailRuangan(&rumahSakit);
        tampilkanInventarisObat(&rumahSakit);
    } else {
        printf("Gagal memuat data rumah sakit.\n");
    }
}