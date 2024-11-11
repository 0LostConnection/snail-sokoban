#include "map.h"
#include <stdio.h>
#include <stdlib.h>

int loadMap(const char *filename, Map *map) {
    FILE *file = fopen(filename, "rb");
    if (!file) return 0;

    fread(&map->width, sizeof(int), 1, file);
    fread(&map->height, sizeof(int), 1, file);

    map->grid = (char **)malloc(map->height * sizeof(char *));
    for (int i = 0; i < map->height; i++) {
        map->grid[i] = (char *)malloc(map->width * sizeof(char));
        fread(map->grid[i], sizeof(char), map->width, file);
    }

    fclose(file);
    return 1;
}

void printMap(Map *map, Player *player) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (i == player->y && j == player->x)
                putchar('@');
            else
                putchar(map->grid[i][j]);
        }
        putchar('\n');
    }
}

void freeMap(Map *map) {
    for (int i = 0; i < map->height; i++) {
        free(map->grid[i]);
    }
    free(map->grid);
}
