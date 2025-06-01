#pragma once

void clearscreen();

void help();
void cekFormatUsn(int *format, User *user);

void cleanInputBuffer();
int getValidIntInput(int min, int max, const char* prompt);
int containsIgnoreCase(const char *haystack, const char *needle);
char toLowerCase(char c);
int strcmpIgnoreCase(const char *str1, const char *str2);
int convertCharToInt(char c);
int convertStringToInt(const char *str);


