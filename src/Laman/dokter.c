#include "dokter.h"

void diagnosis(){
    extern Penyakit *penyakits;
    extern int jumlah_penyakit;

    extern User *pasien; //pasien dari laman dokter

    //kasus tidak ada pasien
    if (pasien == NULL){
        printf("Tidak ada pasien untuk diperiksa!\n");
        return;
    }

    //diagnosis penyakit
    int id_penyakit;
    for (int i = 0; i < jumlah_penyakit; i++){ //cek penyakit
        if (pasien->kondisi.suhu_tubuh > penyakits[i].suhu_tubuh_min && pasien->kondisi.suhu_tubuh < penyakits[i].suhu_tubuh_max) continue;
        if (pasien->kondisi.tekanan_darah_sistolik > penyakits[i].tekanan_darah_sistolik_min && pasien->kondisi.tekanan_darah_sistolik < penyakits[i].tekanan_darah_sistolik_max) continue;
        if (pasien->kondisi.tekanan_darah_diastolik > penyakits[i].tekanan_darah_diastolik_min && pasien->kondisi.tekanan_darah_diastolik < penyakits[i].tekanan_darah_diastolik_max) continue;
        if (pasien->kondisi.detak_jantung > penyakits[i].detak_jantung_min && pasien->kondisi.detak_jantung < penyakits[i].detak_jantung_max) continue;
        if (pasien->kondisi.saturasi_oksigen > penyakits[i].saturasi_oksigen_min && pasien->kondisi.saturasi_oksigen < penyakits[i].saturasi_oksigen_max) continue;
        if (pasien->kondisi.kadar_gula_darah > penyakits[i].kadar_gula_darah_min && pasien->kondisi.kadar_gula_darah < penyakits[i].kadar_gula_darah_max) continue;
        if (pasien->kondisi.berat_badan > penyakits[i].berat_badan_min && pasien->kondisi.berat_badan < penyakits[i].berat_badan_max) continue;
        if (pasien->kondisi.tinggi_badan > penyakits[i].tinggi_badan_min && pasien->kondisi.tinggi_badan < penyakits[i].tinggi_badan_max) continue;
        if (pasien->kondisi.kadar_kolesterol > penyakits[i].kadar_kolesterol_min && pasien->kondisi.kadar_kolesterol < penyakits[i].kadar_kolesterol_max) continue;
        if (pasien->kondisi.trombosit > penyakits[i].trombosit_min && pasien->kondisi.trombosit < penyakits[i].trombosit_max) continue;
        id_penyakit = penyakits[i].id;
        printf("%s terdiagnosa penyakit %s!\n", pasien->identitas.username);
        return;
    }

    //tidak sakit
    printf("%s tidak terdiagnosis penyakit apapun!\n", pasien->identitas.username);
}