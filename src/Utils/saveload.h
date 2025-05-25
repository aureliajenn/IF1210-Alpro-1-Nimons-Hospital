#ifndef SAVELOAD_H
#define SAVELOAD_H

#define MAX_USER 100
#define MAX_LINE_LEN 1024

#include "../Utils/map.h"

void make_folder(const char* path);

void save(const char folder_name[]);

void load(const char *folder_name);

Map *loadConfig(const char *configPath);

#endif