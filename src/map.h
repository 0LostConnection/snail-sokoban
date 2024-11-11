#ifndef MAP_H
#define MAP_H

#include "types.h"  // Inclui o único lugar onde Map é definido

int loadMap(const char *filename, Map *map);
void printMap(Map *map, Player *player);
void freeMap(Map *map);

#endif
