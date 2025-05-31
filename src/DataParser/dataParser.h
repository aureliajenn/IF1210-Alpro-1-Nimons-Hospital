#pragma once

#include "../Model/model.h"

#define MAX_USER 100
#define MAX_LINE_LEN 1024
#define MAX_FIELD 50
#define MAX_COL_LEN 100

typedef struct {
    Penyakit *arr;
    int *jumlah;
} ParsePenyakit;

typedef struct {
    User *arr;
    int *jumlah;
} ParseTarget;

typedef struct {
    Obat *arr;
    int *jumlah;
} ParseObat;

typedef struct {
    ObatPenyakit *arr;
    int *jumlah;
} ParseObatPenyakit;

typedef void (*CSVRowHandler)(char fields[][MAX_COL_LEN],int count,void *target);

void ArrtoCSV(const char *filename, CSVRowHandler handler, void *target);

void writeUsersToFile(char fields[][MAX_COL_LEN], int count, void *target); 

void CSVtoArr(const char *filename, CSVRowHandler handler, void *target);

void handleUserRow(char fields[][MAX_COL_LEN], int count, void *target);

void handlePenyakitRow(char fields[][MAX_COL_LEN], int count, void *target);

void handleObatPenyakitRow(char fields[][MAX_COL_LEN], int count, void *target);

void handleObatRow(char fields[][MAX_COL_LEN], int count, void *target);

void stripNewline(char *str);