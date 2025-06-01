#include "main.h"

int convertCharToInt(char c) {
    return c - '0'; 
}

int convertStringToInt(const char *str) {
    int result = 0;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + convertCharToInt(str[i]);
        } else {
            break;
        }
        i++;
    }
    return result;
}

void clearscreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

char toLowerCase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

int strcmpIgnoreCase(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        char c1 = toLowerCase(*str1);
        char c2 = toLowerCase(*str2);
        
        if (c1 != c2) {
            return c1 - c2;
        }
        
        str1++;
        str2++;
    }
    
    return toLowerCase(*str1) - toLowerCase(*str2);
}

int containsIgnoreCase(const char *haystack, const char *needle) {
    if (!haystack || !needle) return 0;
    if (*needle == '\0') return 1;
    
    int haystackLen = strlen(haystack);
    int needleLen = strlen(needle);
    
    if (needleLen > haystackLen) return 0;
    
    for (int i = 0; i <= haystackLen - needleLen; i++) {
        int match = 1;
        for (int j = 0; j < needleLen; j++) {
            if (toLowerCase(haystack[i + j]) != toLowerCase(needle[j])) {
                match = 0;
                break;
            }
        }
        if (match) return 1;
    }
    
    return 0;
}


void cleanInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}


int getValidIntInput(int min, int max, const char* prompt) {
    int input;
    int valid = 0;
    
    while (!valid) {
        printf("%s", prompt);
        
        if (scanf("%d", &input) != 1) {
            cleanInputBuffer();
            printf("Input tidak valid! Harap masukkan angka.\n");
            continue;
        }
        
        if (input < min || input > max) {
            printf("Input di luar rentang! Masukkan angka antara %d-%d.\n", min, max);
            continue;
        }
        
        valid = 1;
    }
    
    cleanInputBuffer(); 
    return input;
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