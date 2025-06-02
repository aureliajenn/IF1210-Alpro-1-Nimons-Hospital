#include "main.h"

const char *dapatkanUsername(User *users, int userCount, int id, const char *role)
{
    for (int i = 0; i < userCount; i++)
    {
        if (users[i].identitas.id == id)
        {
            if (strcmp(users[i].identitas.role, role) == 0)
            {
                return users[i].identitas.username;
            }
            else
            {
                if (strcmp(role, "dokter") == 0)
                {
                    return "Bukan Dokter";
                }
                else if (strcmp(role, "pasien") == 0)
                {
                    return "Bukan Pasien";
                }
                else
                {
                    return "Role Tidak Valid";
                }
            }
        }
    }
    return "ID Tidak Dikenal";
}

int muatDataRumahSakit(const char *namaFile, Hospital *rumahSakit)
{
    FILE *file = fopen(namaFile, "r");
    if (file == NULL)
    {
        printf("Error: Gagal membuka file %s\n", namaFile);
        return 0;
    }

    char baris[MAX_LINE_LENGTH];
    int hitungBaris = 0;

    rumahSakit->roomCount = 0;
    rumahSakit->medicineCount = 0;

    while (fgets(baris, MAX_LINE_LENGTH, file))
    {
        baris[strcspn(baris, "\n")] = 0;

        hitungBaris++;

        if (hitungBaris == 1)
        {
            char rowsStr[10], colsStr[10];
            int i = 0;

            while (baris[i] >= '0' && baris[i] <= '9')
            {
                rowsStr[i] = baris[i];
                i++;
            }
            rowsStr[i] = '\0';
            rumahSakit->rows = convertStringToInt(rowsStr);

            i++;
            int j = 0;
            while (baris[i] >= '0' && baris[i] <= '9')
            {
                colsStr[j] = baris[i];
                i++;
                j++;
            }
            colsStr[j] = '\0';
            rumahSakit->cols = convertStringToInt(colsStr);
        }
        else if (hitungBaris == 2)
        {
            char maxPatientsStr[10];
            int i = 0;

            while (baris[i] >= '0' && baris[i] <= '9')
            {
                maxPatientsStr[i] = baris[i];
                i++;
            }
            maxPatientsStr[i] = '\0';
            rumahSakit->maxPatientsPerRoom = convertStringToInt(maxPatientsStr);
        }
        else if (hitungBaris <= 8)
        {
            int nilai[MAX_PATIENTS + 1];
            int hitungNilai = 0;
            int i = 0;

            while (baris[i] != '\0')
            {
                if (baris[i] >= '0' && baris[i] <= '9')
                {
                    char temp[10];
                    int j = 0;
                    while (baris[i] >= '0' && baris[i] <= '9')
                    {
                        temp[j] = baris[i];
                        j++;
                        i++;
                    }
                    temp[j] = '\0';
                    nilai[hitungNilai++] = convertStringToInt(temp);
                }
                else
                {
                    i++;
                }
            }

            if (hitungNilai >= 1)
{
    Room *ruangan = &rumahSakit->rooms[rumahSakit->roomCount];
    ruangan->roomIndex = hitungBaris - 3;
    ruangan->doctorId = nilai[0];
    ruangan->patientCount = 0;

    for (int i = 1; i < hitungNilai; i++) {
        if (nilai[i] > 0) {
            ruangan->patients[ruangan->patientCount++] = nilai[i];
        }
    }

    rumahSakit->roomCount++;
}

        }
        else
        {
            int nilai[MAX_PATIENTS];
            int hitungNilai = 0;
            int i = 0;

            while (baris[i] != '\0')
            {
                if (baris[i] >= '0' && baris[i] <= '9')
                {
                    char temp[10];
                    int j = 0;
                    while (baris[i] >= '0' && baris[i] <= '9')
                    {
                        temp[j] = baris[i];
                        j++;
                        i++;
                    }
                    temp[j] = '\0';
                    nilai[hitungNilai++] = convertStringToInt(temp);
                }
                else
                {
                    i++;
                }
            }

            if (hitungNilai >= 1)
            {
                PatientMedicine *obat = &rumahSakit->medicines[rumahSakit->medicineCount];
                obat->patientId = nilai[0];
                obat->medicineCount = hitungNilai - 1;

                for (int i = 0; i < obat->medicineCount; i++)
                {
                    obat->medicines[i] = nilai[i + 1];
                }

                rumahSakit->medicineCount++;
            }
        }
    }

    fclose(file);
    return 1;
}

void tampilkanDenahRumahSakit(Hospital *rumahSakit)
{
    printf("\n      "); // Spasi awal untuk menyelaraskan dengan label baris (A, B, ...)
    for (int j = 1; j <= rumahSakit->cols; j++)
    {
        printf("%-6d", j);
    }
    printf("\n");

    for (int i = 0; i < rumahSakit->rows; i++)
    {
        printf("   "); // Spasi sebelum garis horizontal
        for (int j = 0; j < rumahSakit->cols; j++)
        {
            printf("+-----");
        }
        printf("+\n");

        printf(" %c ", 'A' + i); // Label baris: A, B, C, ...
        for (int j = 0; j < rumahSakit->cols; j++)
        {
            int indeksRuangan = i * rumahSakit->cols + j;
            char labelRuangan[5];
            dapatkanLabelRuangan(indeksRuangan, labelRuangan, rumahSakit->cols);
            printf("| %-4s", labelRuangan);
        }
        printf("|\n");
    }

    // Garis penutup terakhir
    printf("   ");
    for (int j = 0; j < rumahSakit->cols; j++)
    {
        printf("+-----");
    }
    printf("+\n");
}

void tampilkanDetailRuangan(Hospital *rumahSakit, Map *map ,char *kodeRuangan, User *users, int userCount)
{
    int targetIndex = -1;
    for (int i = 0; i < rumahSakit->roomCount; i++)
    {
        char labelRuangan[5];
        dapatkanLabelRuangan(rumahSakit->rooms[i].roomIndex, labelRuangan, rumahSakit->cols);
        if (strcmp(labelRuangan, kodeRuangan) == 0)
        {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1)
    {
        printf("Ruangan %s tidak ditemukan.\n", kodeRuangan);
        return;
    }

    Room ruangan = rumahSakit->rooms[targetIndex];

    printf("\n--- Detail Ruangan %s ---\n", kodeRuangan);
    printf("Kapasitas : %d\n", rumahSakit->maxPatientsPerRoom);

    const char *namaDokter = dapatkanUsername(users, userCount, ruangan.doctorId, "dokter");
    if(strcasecmp(namaDokter,"ID Tidak Dikenal")==0){
        printf("Dokter    : Dokter tidak ada\n");
    }else{
        printf("Dokter    : Dr. %s\n", namaDokter);
    }

    if (ruangan.patientCount == 0)
    {
        printf("Pasien di dalam ruangan:\n");
        printf("Tidak ada pasien di dalam ruangan saat ini.\n");
    }
    else
    {
        printf("Pasien di dalam ruangan:\n");
        Dokter *dokter = getDoctor(map,ruangan.doctorId);
        for (int i = 0; i < dokter->jumlahPasienDalamRuangan; i++)
        {
            const char *namaPasien = dapatkanUsername(users, userCount, ruangan.patients[i], "pasien");
            printf("%d. %s\n", i + 1, namaPasien);
        }
        if(ruangan.patientCount > dokter->jumlahPasienDalamRuangan)
        {printf("\nPasien di luar ruangan:\n");
        for(int i=dokter->jumlahPasienDalamRuangan; i < ruangan.patientCount; i++){
            const char *namaPasien = dapatkanUsername(users, userCount, ruangan.patients[i], "pasien");
            printf("%d. %s\n", i + 1, namaPasien);
        }}
    }

    printf("-------------------------\n");
}

void tampilkanDenahDanMintaDetail(Hospital *rumahSakit,Map *map , User *users, int userCount)
{
    char inputKode[10];

    while (1)
    {
        // Tampilkan denah rumah sakit
        printf("\n===== DENAH RUMAH SAKIT =====\n");
        tampilkanDenahRumahSakit(rumahSakit);

        // Minta user memilih kode ruangan
        printf("Masukkan kode ruangan untuk masuk (ketik 'exit' untuk keluar): ");
        scanf("%9s", inputKode);

        if (strcmp(inputKode, "exit") == 0)
            break;

        int targetIndex = -1;
        for (int i = 0; i < rumahSakit->roomCount; i++)
        {
            char labelRuangan[5];
            dapatkanLabelRuangan(rumahSakit->rooms[i].roomIndex, labelRuangan, rumahSakit->cols);
            if (strcmp(labelRuangan, inputKode) == 0)
            {
                targetIndex = i;
                break;
            }
        }

        if (targetIndex == -1)
        {
            printf("Ruangan %s tidak ditemukan.\n", inputKode);
            continue;
        }

        // Masuk ke ruangan
        printf("\n=== Anda berada di ruangan %s ===\n", inputKode);
        tampilkanDetailRuangan(rumahSakit, map, inputKode, users, userCount);
        waitForEnter();
    }

    printf("Kembali ke menu utama.\n");
}

void tampilkanSemuaAntrianUntukManajer(Hospital *rumahSakit, Map *map, User *users, int userCount)
{
    printf("\n===== SEMUA ANTRIAN DI RUMAH SAKIT =====\n");
    tampilkanDenahRumahSakit(rumahSakit);

    for (int i = 0; i < rumahSakit->roomCount; i++) {
        Room *room = &rumahSakit->rooms[i];

        if (room->doctorId == -1)
            continue;  // Lewati ruangan tanpa dokter

        // Dapatkan label ruangan, misalnya "A1"
        char labelRuangan[5];
        dapatkanLabelRuangan(room->roomIndex, labelRuangan, rumahSakit->cols);

        // Ambil data dokter dari Map berdasarkan ID dokter
        Dokter *dokter = getDoctor(map, room->doctorId);
        if (!dokter) {
            printf("\n=== Ruangan %s (Dokter tidak ada) ===\n", labelRuangan);
            tampilkanDetailRuangan(rumahSakit, map, labelRuangan, users, userCount);
            continue;
        }

        printf("\n=== Ruangan %s (Dokter ID: %d) ===\n", labelRuangan, dokter->id);
        tampilkanDetailRuangan(rumahSakit, map, labelRuangan, users, userCount);
    }

    printf("\n[SELESAI] Semua ruangan telah ditampilkan.\n");
}

void tampilkanInventarisObat(Hospital *rumahSakit)
{
    printf("\nInventaris Obat Pasien:\n");
    for (int i = 0; i < rumahSakit->medicineCount; i++)
    {
        printf("Pasien ID %d: ", rumahSakit->medicines[i].patientId);
        if (rumahSakit->medicines[i].medicineCount == 0)
        {
            printf("Tidak ada obat\n");
        }
        else
        {
            printf("Obat: ");
            for (int j = 0; j < rumahSakit->medicines[i].medicineCount; j++)
            {
                printf("%d", rumahSakit->medicines[i].medicines[j]);
                if (j < rumahSakit->medicines[i].medicineCount - 1)
                {
                    printf(", ");
                }
            }
            printf("\n");
        }
    }
}

void dapatkanLabelRuangan(int index, char *labelRuangan, int cols)
{
    // Misal: indeks ke-0 = A1, indeks ke-1 = A2, dst.
    int row = index / cols;
    int col = index % cols + 1;
    labelRuangan[0] = 'A' + row;
    sprintf(labelRuangan + 1, "%d", col);
}