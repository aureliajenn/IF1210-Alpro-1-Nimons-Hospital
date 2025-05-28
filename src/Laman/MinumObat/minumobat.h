#ifndef MINUMOBAT_H
#define MINUMOBAT_
#include "../../Model/model.h"
#include "../../ADT/stack.h"

void tampilkanDaftarObat(Obat inventory[], int jumlahObat);
/*Proses: Menampilkan daftar obat. */
/*I.S. Inventory terdefinisi, dan jumlahObat adalah jumlah elemen dalam array*/
/*F.S. Daftar obat ditampilkan ke layar dengan format bernomor.*/

void lamanMinumObat();
/*Proses: Menampilkan daftar obat dalam inventory user, menerima input pilihan obat yang ingin diminum, memindahkannya ke stack perut, dan menghapus obat tersebut dari inventory user*/
/*I.S. User sedang login dan merupakan pasien. user->obat berisi daftar obat yang dimiliki dan user->jumlahObat menyatakan jumlahnya*/
/*F.S. 1. Jika user bukan pasien → pesan error ditampilkan. */
/*     2. Jika inventory kosong → pesan ditampilkan. */
/*     3. Jika input tidak valid → pesan kesalahan ditampilkan. */
/*     4. Jika input valid: */
/*            a. Obat yang dipilih dimasukkan ke stack perut user.*/
/*            b. Obat tersebut dihapus dari inventory (elemen bergeser).*/
/*            c. Jumlah obat dikurangi satu.*/
/*            d. Daftar sisa obat ditampilkan jika masih ada.*/

#endif