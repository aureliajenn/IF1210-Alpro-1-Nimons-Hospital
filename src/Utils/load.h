#pragma once

void load(const char *folder_name);
void loadConfig(const char *configPath);
// void loadObat(const char *filePath);
const char *getNamaObat(int id);

void parseDuaAngka(const char *str, int *a, int *b) ;
int parseAngka(const char *str, int *hasil) ;
User* getUserById(int id) ;
void updateUsers(User user);
void hapusElemenArray(int array[], int *length, int index) ;