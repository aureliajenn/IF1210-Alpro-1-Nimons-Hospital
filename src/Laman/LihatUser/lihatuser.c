#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lihatuser.h"
#include "../CariUser/cariuser.h"

int lamanLihatUser()
{
    extern User *users;
    extern int jumlah_user;

    int by, order;
    printf("Urutkan berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf(">>> Pilihan: ");
    scanf("%d", &by);

    if(by==1){
        printf("\nUrutan sort?\n");
        printf("1. ASC (1-100)\n");
        printf("2. DESC (100-1)\n");
        printf(">>> Pilihan: ");
        scanf("%d", &order);
    }else if(by==2){
        printf("\nUrutan sort?\n");
        printf("1. ASC (A-Z)\n");
        printf("2. DESC (Z-A)\n");
        printf(">>> Pilihan: ");
        scanf("%d", &order);
    }

    User *copy = malloc(jumlah_user * sizeof(User));
    for (int i = 0; i < jumlah_user; i++)
    {
        copy[i] = users[i];
    }

    // Sorting
    for (int i = 0; i < jumlah_user - 1; i++)
    {
        for (int j = i + 1; j < jumlah_user; j++)
        {
            int compare = 0;
            if (by == 1)
                compare = copy[i].identitas.id - copy[j].identitas.id;
            else
                compare = strcmp(copy[i].identitas.username, copy[j].identitas.username);

            if ((order == 1 && compare > 0) || (order == 2 && compare < 0))
            {
                User temp = copy[i];
                copy[i] = copy[j];
                copy[j] = temp;
            }
        }
    }

    printf("\nMenampilkan semua pengguna dengan %s terurut %s...\n",
           by == 1 ? "ID" : "Nama",
           order == 1 ? "ascending" : "descending");

    printf("+------------+---------------------+------------+--------------------+\n");
    printf("| %-10s | %-19s | %-10s | %-18s |\n", "ID", "Nama", "Role", "Penyakit");
    printf("+------------+---------------------+------------+--------------------+\n");

    for (int i = 0; i < jumlah_user; i++)
    {
        printf("| %-10d | %-19s | %-10s | %-18s |\n",
               copy[i].identitas.id,
               copy[i].identitas.username,
               copy[i].identitas.role,
               strcmp(copy[i].identitas.role, "PASIEN") == 0 ? copy[i].kondisi.riwayat_penyakit : "-");
    }

    printf("+------------+---------------------+------------+--------------------+\n");

    free(copy);
    int selectSearchUser;
    printf("\nApakah anda ingin mencari user?\n");
    printf("1. Iya\n");
    printf("2. Tidak\n");
    printf(">>> Pilihan: ");
    scanf("%d", &selectSearchUser);

    if(selectSearchUser == 1) {
        clearScreen();
        return lamanCariUser(by);
        

    } else {
        return 1;
    }

    return 1;
}
