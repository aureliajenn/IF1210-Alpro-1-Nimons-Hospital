#include "main.h"

int lamanCariUser(int by)
{
    extern User *users;
    int selectOpt;
    char searchTerm[MAX_LINE_LEN];

    printf(">>> Pilih apa yang mau dicari\n");
    printf("1. Cari User (Pasien dan Dokter)\n");
    printf("2. Cari Pasien\n");
    printf("3. Cari Dokter\n");

    selectOpt = getValidIntInput(1, 3, ">>> Pilihan: ");

    if(by == -1) {
        if(selectOpt == 3) {
            printf("Cari berdasarkan?\n");
            printf("1. ID\n");
            printf("2. Nama\n");
            by = getValidIntInput(1, 2, ">>> Pilihan: ");
        } else {
            printf("Cari berdasarkan?\n");
            printf("1. ID\n");
            printf("2. Nama\n");
            printf("3. Riwayat Penyakit\n");
            by = getValidIntInput(1, 3, ">>> Pilihan: ");
        }
        
        


    }

    

    switch (selectOpt)
    {
        case 1:
            printf(">>> Masukkan %s User: ", by == 1 ? "ID" : "Nama");            
            scanf("%s", &searchTerm);
            queryAndPrintUserTable(by, searchTerm, users, "ALL");
            break;
        case 2:
            printf(">>> Masukkan %s Pasien:" ,  by ==1 ? "ID" : by ==2 ? "Nama" : "Riwayat Penyakit");
            scanf("%s", &searchTerm);
            queryAndPrintUserTable(by, searchTerm, users, "Pasien");
            break;
        case 3:
            printf(">>> Masukkan %s Dokter:",  by ==1 ? "ID" : "Nama");
            scanf("%s", &searchTerm);
            queryAndPrintUserTable(by, searchTerm, users, "Dokter");
            break;
        default:
            printf("Pilihan tidak valid!\n");
            return 0;
    }
    
}


void queryAndPrintUserTable(int by, char searchTerm[MAX_LINE_LEN], User *users, char role[MAX_LINE_LEN]) {
    extern int jumlah_user;
    int found = 0;

    if (by == 1) {
        int searchId = atoi(searchTerm);
        int left = 0, right = jumlah_user - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int cmp = users[mid].identitas.id - searchId;
            if (cmp == 0) {
                if (strcmp(role, "ALL") == 0 || strcmp(users[mid].identitas.role, role) == 0) {
                    printf("Menampilkan pengguna dengan ID %d:\n", searchId);
                    printf("+------------+---------------------+------------+--------------------+\n");
                    printf("| %-10s | %-19s | %-10s | %-18s |\n", "ID", "Nama", "Role", "Penyakit");
                    printf("+------------+---------------------+------------+--------------------+\n");
                    printf("| %-10d | %-19s | %-10s | %-18s |\n",
                        users[mid].identitas.id,
                        users[mid].identitas.username,
                        users[mid].identitas.role,
                        strcmp(users[mid].identitas.role, "PASIEN") == 0 ? users[mid].kondisi.riwayat_penyakit : "-");
                    printf("+------------+---------------------+------------+--------------------+\n");
                    found = 1;
                }
                break;
            } else if (cmp < 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (!found) {
            printf("User dengan ID %d dan role %s tidak ditemukan.\n", searchId, role);
        }
    } else if (by == 2) {
        for (int i = 0; i < jumlah_user; i++) {
            if (strcmpIgnoreCase(users[i].identitas.username, searchTerm) == 0 &&
                (strcmpIgnoreCase(role, "ALL") == 0 || strcmpIgnoreCase(users[i].identitas.role, role) == 0)) {
                if (!found) {
                    printf("Menampilkan pengguna dengan nama %s:\n", searchTerm);
                    printf("+------------+---------------------+------------+--------------------+\n");
                    printf("| %-10s | %-19s | %-10s | %-18s |\n", "ID", "Nama", "Role", "Penyakit");
                    printf("+------------+---------------------+------------+--------------------+\n");
                }
                printf("| %-10d | %-19s | %-10s | %-18s |\n",
                    users[i].identitas.id,
                    users[i].identitas.username,
                    users[i].identitas.role,
                    (strcmpIgnoreCase(users[i].identitas.role, "PASIEN") == 0 && strlen(users[i].kondisi.riwayat_penyakit) > 0) ? users[i].kondisi.riwayat_penyakit : "-");
                found = 1;
            }
        }
        if (found) {
            printf("+------------+---------------------+------------+--------------------+\n");
        } else {
            printf("User dengan Nama %s dan role %s tidak ditemukan.\n", searchTerm, role);
        }

    } else if (by == 3) {
        for (int i = 0; i < jumlah_user; i++) {
            if (strcmpIgnoreCase(users[i].kondisi.riwayat_penyakit, searchTerm) == 0 &&
                (strcmpIgnoreCase(role, "ALL") == 0 || strcmpIgnoreCase(users[i].identitas.role, role) == 0)) {
                if (!found) {
                    printf("Menampilkan pengguna dengan riwayat penyakit %s:\n", searchTerm);
                    printf("+------------+---------------------+------------+--------------------+\n");
                    printf("| %-10s | %-19s | %-10s | %-18s |\n", "ID", "Nama", "Role", "Penyakit");
                    printf("+------------+---------------------+------------+--------------------+\n");
                }
                printf("| %-10d | %-19s | %-10s | %-18s |\n",
                    users[i].identitas.id,
                    users[i].identitas.username,
                    users[i].identitas.role,
                    (strcmpIgnoreCase(users[i].identitas.role, "PASIEN") == 0 && strlen(users[i].kondisi.riwayat_penyakit) > 0) ? users[i].kondisi.riwayat_penyakit : "-");
                found = 1;
            }
        }
        if (found) {
            printf("+------------+---------------------+------------+--------------------+\n");
        } else {
            printf("User dengan Riwayat Penyakit %s dan role %s tidak ditemukan.\n", searchTerm, role);
        }
    }
}