#include "main.h"

void ArrtoCSV(const char *filename, CSVRowHandler handler, void *target){
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Gagal membuka file");
        exit(1);
    }

    handler(NULL, -1, file);

    fclose(file);
}

void CSVtoArr(const char *filename, CSVRowHandler handler, void *target) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Gagal membuka file");
        exit(1);
    }
    
    char line[MAX_LINE_LEN];
    fgets(line, sizeof(line), file); // skip header

    while (fgets(line, sizeof(line), file)) {
        char fields[MAX_FIELD][MAX_COL_LEN] = {0};
        int fieldIdx = 0, charIdx = 0;

        for (int i = 0; ; i++) {
            char c = line[i];
            if (c == ';' || c == '\n' || c == '\0') {
                fields[fieldIdx][charIdx] = '\0';
                fieldIdx++;
                charIdx = 0;
                if (c == '\n' || c == '\0') break;
            } else {
                if (charIdx < MAX_COL_LEN - 1) {
                    fields[fieldIdx][charIdx++] = c;
                }
            }
        }

        handler(fields, fieldIdx, target);
    }
    fclose(file);
}

void handleUserRow(char fields[][MAX_COL_LEN], int count, void *target) {
    ParseTarget *pt = (ParseTarget *)target;  // cast target ke struct kita

    User u;
    u.identitas.id = atoi(fields[0]);
    stripNewline(fields[1]);
    strcpy(u.identitas.username, fields[1]);
    stripNewline(fields[2]);
    strcpy(u.identitas.password, fields[2]);
    stripNewline(fields[3]);
    strcpy(u.identitas.role, fields[3]);
    stripNewline(fields[4]);
    strcpy(u.kondisi.riwayat_penyakit, fields[4]);
    u.kondisi.suhu_tubuh = atof(fields[5]);
    u.kondisi.tekanan_darah_sistolik = atoi(fields[6]);
    u.kondisi.tekanan_darah_diastolik = atoi(fields[7]);
    u.kondisi.detak_jantung = atoi(fields[8]);
    u.kondisi.saturasi_oksigen = atof(fields[9]);
    u.kondisi.kadar_gula_darah = atoi(fields[10]);
    u.kondisi.berat_badan = atof(fields[11]);
    u.kondisi.tinggi_badan = atoi(fields[12]);
    u.kondisi.kadar_kolesterol = atoi(fields[13]);
    u.kondisi.trombosit = atoi(fields[14]);

    u.kondisi.jumlahObat = 0;  // kosong saat awal

    // Inisialisasi StackPerut
    u.kondisi.perut.items = malloc(10 * sizeof(Obat)); // alokasi awal
    u.kondisi.perut.top = -1;
    u.kondisi.perut.capacity = 10;
    u.kondisi.sudahDiobati = 0;
    u.kondisi.sudahDiagnosis = (strlen(u.kondisi.riwayat_penyakit) > 0) ? 1 : 0;

    pt->arr[(*pt->jumlah)++] = u;
}


void handlePenyakitRow(char fields[][MAX_COL_LEN], int count, void *target) {
    ParsePenyakit *pp = (ParsePenyakit *)target;  // cast target ke struct kita

    Penyakit p;
    p.id = atoi(fields[0]);
    stripNewline(fields[1]);
    strcpy(p.nama, fields[1]);
    p.suhu_tubuh_min = atof(fields[2]);
    p.suhu_tubuh_max = atof(fields[3]);
    p.tekanan_darah_sistolik_min = atoi(fields[4]);
    p.tekanan_darah_sistolik_max = atoi(fields[5]);
    p.tekanan_darah_diastolik_min = atoi(fields[6]);
    p.tekanan_darah_diastolik_max = atoi(fields[7]);
    p.detak_jantung_min = atoi(fields[8]);
    p.detak_jantung_max = atoi(fields[9]);
    p.saturasi_oksigen_min = atof(fields[10]);
    p.saturasi_oksigen_max = atof(fields[11]);
    p.kadar_gula_darah_min = atoi(fields[12]);
    p.kadar_gula_darah_max = atoi(fields[13]);
    p.berat_badan_min = atof(fields[14]);
    p.berat_badan_max = atof(fields[15]);
    p.tinggi_badan_min = atoi(fields[16]);
    p.tinggi_badan_max = atoi(fields[17]);
    p.kadar_kolesterol_min = atoi(fields[18]);
    p.kadar_kolesterol_max = atoi(fields[19]);
    p.trombosit_min = atoi(fields[20]);
    p.trombosit_max = atoi(fields[21]);

    pp->arr[(*pp->jumlah)++] = p;
}

void handleObatRow(char fields[][MAX_COL_LEN], int count, void *target) {
    ParseObat *po = (ParseObat *)target;

    Obat o;
    o.id = atoi(fields[0]);
    stripNewline(fields[1]);
    strcpy(o.nama, fields[1]);
    po->arr[(*po->jumlah)++] = o;
}

void handleObatPenyakitRow(char fields[][MAX_COL_LEN], int count, void *target) {
    ParseObatPenyakit *pop = (ParseObatPenyakit *)target;

    ObatPenyakit op;
    op.obat_id = atoi(fields[0]);
    op.penyakit_id = atoi(fields[1]);
    op.urutan_minum = atoi(fields[2]);
    pop->arr[(*pop->jumlah)++] = op;
}

void stripNewline(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\r' || str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}