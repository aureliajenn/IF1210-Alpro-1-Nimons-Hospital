#include "utils.h"


void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void cekFormatUsn(int *format, User *user)
{
    do
    {
        *format = 1;
        printf("Username: ");
        scanf("%s", user->identitas.username);
        for (int i = 0; user->identitas.username[i] != '\0'; i++)
        {
            if (user->identitas.username[i] < 'A' || (user->identitas.username[i] > 'Z' && user->identitas.username[i] < 'a') || user->identitas.username[i] > 'z')
            {
                *format = 0;
                printf("Format username hanya boleh huruf! Ulangi.\n");
                break;
            }
        }
    } while (!*format);
}