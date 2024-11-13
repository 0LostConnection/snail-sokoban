#include "../lib/map.h"
#include "../lib/player.h"
#include "../lib/base.h"

#include "stdio.h"
#include "stdlib.h"

Map initMap(const char *file_path) {
    int map_col, map_lgn, pos_x, pos_y;

    FILE *file = fopen(file_path, "rb");

    if (!file) {
        printf("Erro: não foi possível ler o arquivo!\n");
        return NULL;
    }

    // Lendo as dimensões do mapa e a posição inicial do jogador
    fread(&map_lgn, sizeof(int), 1, file);
    fread(&map_col, sizeof(int), 1, file);
    fread(&pos_x, sizeof(int), 1, file);
    fread(&pos_y, sizeof(int), 1, file);

    // Inicializando a struct Map
    Map map = (Map) malloc(sizeof(StrMap));
    map->nb_col = map_col;
    map->nb_lgn = map_lgn;
    map->grid = (Characters **) malloc(map_lgn * sizeof(Characters *));

    // Alocando cada linha da grid
    for (int i = 0; i < map_lgn; i++) {
        map->grid[i] = (Characters *) malloc(map_col * sizeof(Characters));
        // Lendo uma linha completa do mapa
        //fread(map->grid[i], sizeof(Characters), map_col, file);
    }
    int current_line = 1;
    int end_line = map_lgn + current_line;
    int col, lgn = 0;
    char line[100];
    fread(line, sizeof(char), 100, file);
    while (current_line < end_line) {
        col = 0;
        fread(line, sizeof(char), 100, file);
        while (col < map_col) {
            map->grid[lgn][col] = line[col];
            col++;
        }
        lgn++;
        current_line++;
    }
    
    // Configurando a posição do jogador
    Player p;
    p.posX = pos_x;
    p.posY = pos_y;
    map->player = p;

    fclose(file);
    return map;
}

void display_map(Map map) {
    int cols = 0;
    int rows = 0;
    tc_get_cols_rows(&cols, &rows);
    int i;
    for (i = 0; i < map->nb_lgn; i++) {
        tc_move_cursor((int) (cols / 2 - map->nb_col / 2), (int) rows / 3 + i);
        for (int j = 0; j < map->nb_col; j++) {
            if (map->grid[i][j] == CLOSED_GOAL) {
                printf("%s%c%s", TC_RED, BOX, TC_NRM);
            } else if (i == map->player.posY && j == map->player.posX) {
                printf("%s%c%s", TC_GRN, PLAYER, TC_NRM);
            } else if (map->grid[i][j] == OPEN_GOAL) {
                printf("%s%c%s", TC_YEL, OPEN_GOAL, TC_NRM);
            } else if (map->grid[i][j] == BOX) {
                printf("%s%c%s", TC_MAG, BOX, TC_NRM);
            } else if (map->grid[i][j] == WALL) {
                printf("%s%c%s", TC_BLU, WALL, TC_NRM);
            } else {
                printf("%c", map->grid[i][j]);
            }
        }

        printf("\n");
    }
    tc_move_cursor((int) (cols / 2 - 6), (int) rows / 3 + i + 1);
}
