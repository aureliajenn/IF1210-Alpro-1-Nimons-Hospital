#ifndef STACK_H
#define STACK_H

#include "../../Model/model.h"
#include "../../Utils/Boolean.h"

void initPerutStack(StackPerut *stack, int capacity);
/*Proses: Menginisialisasi stack kosong dengan kapasitas tertentu dan mengalokasikan memori untuk array penampung elemen stack. */
/*I.S. stack sudah dialokasikan tetapi belum memiliki array penampung serta nilai top dan capacity belum terdefinisi. */
/*F.S. stack kosong dengan array items sebesar capacity, top bernilai -1, dan capacity sudah diinisialisasi. */

bool isPerutFull(StackPerut *stack);
/*Proses: Mengecek apakah stack penuh.*/
/*I.S. stack terinisialisasi.*/
/*F.S. mengirimkan true jika stack penuh, dan false jika tidak.*/

bool isPerutEmpty(StackPerut *stack);
/*Proses: Mengecek apakah stack kosong.*/
/*I.S. stack terinisialisasi.*/
/*F.S. mengirimkan true jika stack kosong, dan false jika tidak.*/

int pushToPerut(User *user, int obatId, const char *obatNama);
/*Proses: Menambahkan elemen obat baru ke stack.*/
/*I.S. Stack terdefinisi, mungkin penuh. Parameter obatId dan obatNama diberikan.*/
/*F.S. Obat baru dengan obatId dan obatNama berada di puncak stack. top bertambah 1.*/
/*     Mengembalikan 1 jika berhasil, 0 jika stack penuh (tidak terjadi perubahan).*/

int popFromPerut(User *user, Obat *obat);
/*Proses: Menghapus elemen obat dari puncak stack.*/
/*I.S. Stack terdefinisi, mungkin kosong.*/
/*F.S. Elemen puncak stack dikeluarkan dan disimpan ke obat, top berkurang 1.*/
/*      Mengembalikan 1 jika berhasil, 0 jika stack kosong (tidak terjadi perubahan).*/

#endif