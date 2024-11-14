#ifndef MAP_H
#define MAP_H

#include "player.h"

typedef enum Characters {
    WALL = '#',
    BOX = 'x',
    PLAYER = '@',
    OPEN_GOAL = 'o',
    CLOSED_GOAL = '*',
    NONE = ' '
} Characters;

typedef struct map {
    char **grid;
    int height;
    int width;
    Player player;
} StrMap, *Map;

Map init_map(const char *file_path);

void display_map(Map map);

#endif
