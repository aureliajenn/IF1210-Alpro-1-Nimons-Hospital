#include "main.h"

void pulangdok() {
	extern User *user;
    extern Map *map;
    extern Hospital rumahSakit; 
    int equal = 1;
    extern User *users;
    extern int jumlah_user;
	//asumsi ada urutan obat yang harus diminum dari proses ngobatin atau getUrutanObat(char* namapenyakit)
	//Stack urutanMinumObat;
	//TODO: tambahkan pulangdok ke laman pasien, load obat_penyakit.csv, masukkan urutanMinumObat, pindahkan kode keluar antrian ke bagian akhir
	
	for (int i = 0; i < map->size; i++)
    {
        if (map->dokter[i]->queue != NULL)
        {
            QueueNode *current = map->dokter[i]->queue->front;
            while (current != NULL)
            {
                if (current->patient.id == user->identitas.id)
                {
                    strcpy(user->kondisi.riwayat_penyakit, current->patient.riwayat_penyakit);
                    break;
                }
                current = current->next;
            }
        }
    }
	
	if (strlen(user->kondisi.riwayat_penyakit) == 0) {
		printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");
		return;
	}
	
	printf("Dokter sedang memeriksa keadaanmu...\n\n");
	
	/*
	
	if (urutanMinumObat.top > user->kondisi.StackPerut.top) {
		printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
		return;
	}
	if (urutanMinumObat.top != user->kondisi.StackPerut.top) {
		equal = 0;
	}
	
	for (int i = 0; i <= user->kondisi.StackPerut.top; i++) {
		if (urutanMinumObat.items[i].id != user->kondisi.StackPerut.items[i].id || equal == 0) {
			equal = 0;
			break;
		}
	}
	
	if (equal == 0) {
		printf("Maaf, tapi kamu masih belum bisa pulang!\n\n");
		printf("Urutan peminuman obat yang diharapkan:\n");
		for (int i = 0; i <= urutanMinumObat.top; i++) {
			printf("%s", urutanMinumObat.items[i].nama);
			if (i < urutanMinumObat.top) {
				printf(" -> ");
			}
		}
		printf("\n\nUrutan obat yang kamu minum:\n");
		for (int i = 0; i <= user->kondisi.StackPerut.top; i++) {
			if (urutanMinumObat.items[i].id != user->kondisi.StackPerut.items[i].id) {
				printf("\033[1;31m");
			}
			printf("%s\033[m", user->kondisi.StackPerut.items[i].nama);
			if (i < user->kondisi.StackPerut.top) {
				printf(" -> ");
			}
		}
		printf("\n\nSilahkan kunjungi dokter untuk meminta penawar yang sesuai!\n");
		return;
	}
	
	printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");
	free(user->kondisi);
	//pindahkan kode keluar dari antrian dari bagian Diagnosis ke sini setelah Ngobatin dan minumPenawar selesai
	*/
}