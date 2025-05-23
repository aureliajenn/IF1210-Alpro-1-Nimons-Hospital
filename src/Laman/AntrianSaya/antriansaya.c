#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "antriansaya.h"


int lamanLihatAntrianSaya()
{
    extern User *user;
    extern Map *map;
    int found = 0;
    extern User *users;
    extern int jumlah_user;

    if (map == NULL)
    {
        printf("Map tidak ditemukan!\n");
        return 0;
    }

    for (int i = 0; i < map->size; i++)
    {
        if (map->dokter[i]->queue != NULL)
        {
            QueueNode *current = map->dokter[i]->queue->front;

            while (current != NULL)
            {
                if (current->patient.id == user->identitas.id)
                {
                    char *dokterName = "DOKTER TIDAK DITEMUKAN";
                    for (int j = 0; j < jumlah_user; j++) {
                        if (strcmpIgnoreCase(users[j].identitas.role, "dokter") == 0 && users[j].identitas.id == map->dokter[i]->id) {
                            dokterName = users[j].identitas.username; 
                            break;
                        }
                    }

                    char labelRuangan[5];
                    dapatkanLabelRuangan(map->dokter[i]->ruangan, labelRuangan, map->cols);
                    printf("STATUS ANTRIAN ANDA:\n");
                    printf("NAMA: %s\n", user->identitas.username);
                    printf("DOKTER: %s\n", dokterName);
                    printf("RUANGAN: %s\n",labelRuangan);
                    printf("POSISI ANTRIAN: %d dari %d\n", getQueuePosition(map->dokter[i]->queue, user->identitas.id), map->dokter[i]->queueLength);
                    found = 1;
                    break;
                }
                current = current->next;
            }
        }
    }

    if (!found)
    {
        printf("Anda belum terdaftar dalam antrian check-up!\nSilakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
    }

    return 1;
}