#include "../lib/map.h"
#include "../lib/player.h"
#include "../lib/base.h"

#include "stdio.h"
#include "stdlib.h"

Map init_map(int current_level) {
    // Cria o caminho do arquivo com o número da fase
    char file_path[20];
    sprintf(file_path, "fase%d.dat", current_level);

    FILE *file = fopen(file_path, "rb");
    if (!file) return NULL;

    Map map = (Map) malloc(sizeof(struct map));

    fread(&map->width, sizeof(int), 1, file);
    fread(&map->height, sizeof(int), 1, file);
    fread(&map->player.posX, sizeof(int), 1, file);
    fread(&map->player.posY, sizeof(int), 1, file);

    map->grid = (char **) malloc(map->height * sizeof(char *));
    for (int i = 0; i < map->height; i++) {
        map->grid[i] = (char *) malloc(map->width * sizeof(char));
        fread(map->grid[i], sizeof(char), map->width, file);
    }

    fclose(file);

    return map;
}

void display_map(Map map) {
    int cols = 0;
    int rows = 0;
    int i;

    get_cols_rows(&cols, &rows);

    for (i = 0; i < map->height; i++) {
        move_cursor(((cols - map->width) / 2), rows / 3 + i);

        for (int j = 0; j < map->width; j++) {
            if (map->grid[i][j] == CLOSED_GOAL) {
                printf("%s%c%s", TC_RED, CLOSED_GOAL, TC_NRM);
            } else if (i == map->player.posY && j == map->player.posX) {
                printf("%s%c%s", TC_GRN, PLAYER, TC_NRM);
            } else if (map->grid[i][j] == OPEN_GOAL) {
                printf("%s%c%s", TC_YEL, OPEN_GOAL, TC_NRM);
            } else if (map->grid[i][j] == BOX) {
                printf("%s%c%s", TC_MAG, BOX, TC_NRM);
            } else if (map->grid[i][j] == WALL) {
                printf("%s%c%s", TC_BLU, WALL, TC_NRM);
            } else if (map->grid[i][j] == PLAYER) {
                printf("%s%c%s", TC_GRN, PLAYER, TC_NRM);
            } else {
                printf("%c", map->grid[i][j]);
            }
        }
        putchar('\n');
    }
    move_cursor((cols / 2 - 6), rows / 3 + i + 1);
}

void free_map(Map map) {
    if (map != NULL) {
        // Libera cada linha da grid
        for (int i = 0; i < map->height; i++) {
            free(map->grid[i]);
        }
        // Libera o array de ponteiros da grid
        free(map->grid);
        // Libera a estrutura map
        free(map);
    }
}
