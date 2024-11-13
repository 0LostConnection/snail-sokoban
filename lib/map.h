#ifndef MAP_H
#define MAP_H

#include "player.h"

typedef enum Characters{
    WALL = '#',
    BOX = 'x',
    PLAYER = 'p',
    OPEN_GOAL = 'o',
    CLOSED_GOAL = '*',
    NONE = ' '
} Characters;

typedef struct map {
    enum Characters** grid;
    int nb_col;
    int nb_lgn;
    Player player;
} StrMap, *Map;

Map initMap(const char* file_path);

void display_map(Map map);

#endif