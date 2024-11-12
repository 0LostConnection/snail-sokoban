#ifndef MAP_H
#define MAP_H

#include "player.h"

typedef enum Characters{
    PLAYER = 'p',
    NONE = ' '
} Characters;

typedef struct map {
    enum Characters** grid;
    int nb_col;
    int nb_lgn;
    Player player;
} StrMap, *Map;

Map initMap(const char* file_path, int level);

void display_map(Map map);

#endif