#include "main.h"

int muatDataRumahSakit(const char *namaFile, Hospital *rumahSakit){
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
            char rowsStr[10], colsStr[10];
            int i = 0;
            
            while (baris[i] >= '0' && baris[i] <= '9') {
                rowsStr[i] = baris[i];
                i++;
            }
            rowsStr[i] = '\0'; 
            rumahSakit->rows = convertStringToInt(rowsStr);
            
            i++;  
            int j = 0;
            while (baris[i] >= '0' && baris[i] <= '9') {
                colsStr[j] = baris[i];
                i++;
                j++;
            }
            colsStr[j] = '\0'; 
            rumahSakit->cols = convertStringToInt(colsStr);
        } else if (hitungBaris == 2) {
            char maxPatientsStr[10];
            int i = 0;
            
            while (baris[i] >= '0' && baris[i] <= '9') {
                maxPatientsStr[i] = baris[i];
                i++;
            }
            maxPatientsStr[i] = '\0';
            rumahSakit->maxPatientsPerRoom = convertStringToInt(maxPatientsStr);
        } else if (hitungBaris <= 8) {
            int nilai[MAX_PATIENTS + 1]; 
            int hitungNilai = 0;
            int i = 0;

            while (baris[i] != '\0') {
                if (baris[i] >= '0' && baris[i] <= '9') {
                    char temp[10];
                    int j = 0;
                    while (baris[i] >= '0' && baris[i] <= '9') {
                        temp[j] = baris[i];
                        j++;
                        i++;
                    }
                    temp[j] = '\0';  
                    nilai[hitungNilai++] = convertStringToInt(temp);
                } else {
                    i++;
                }
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
            int hitungNilai = 0;
            int i = 0;
            
            while (baris[i] != '\0') {
                if (baris[i] >= '0' && baris[i] <= '9') {
                    char temp[10];
                    int j = 0;
                    while (baris[i] >= '0' && baris[i] <= '9') {
                        temp[j] = baris[i];
                        j++;
                        i++;
                    }
                    temp[j] = '\0';  
                    nilai[hitungNilai++] = convertStringToInt(temp);
                } else {
                    i++;
                }
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
        
        int foundPasien = 0;
        for (int j = 0; j < rumahSakit->rooms[i].patientCount; j++) {
            if (rumahSakit->rooms[i].patients[j] > 0) {
                foundPasien = 1;
                break;
            }
        }

        if (!foundPasien) {
            printf("Tidak ada pasien\n");
        } else {
            printf("Pasien: ");
            int printed = 0;
            for (int j = 0; j < rumahSakit->rooms[i].patientCount; j++) {
                int id = rumahSakit->rooms[i].patients[j];
                if (id > 0) {
                    if (printed > 0) printf(", ");
                    printf("%d", id);
                    printed++;
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

void tampilkanDenahRS() {
    extern Hospital *rumahSakit;

        tampilkanDenahRumahSakit(rumahSakit);
        tampilkanDetailRuangan(rumahSakit);
        tampilkanInventarisObat(rumahSakit);
}