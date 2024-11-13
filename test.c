#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
    int p_x;
    int p_y;
    char **grid;
} Map;

void freeMap(Map *map) {
    for (int i = 0; i < map->height; i++) {
        free(map->grid[i]);
    }
    free(map->grid);
}

int main() {
    FILE *file = fopen("fase1.dat", "rb");
    if (!file) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    Map map;

    // Reading map dimensions and player position
    fread(&map.width, sizeof(int), 1, file);
    fread(&map.height, sizeof(int), 1, file);
    fread(&map.p_x, sizeof(int), 1, file);
    fread(&map.p_y, sizeof(int), 1, file);

    // Allocating memory for the grid
    map.grid = (char **)malloc(map.height * sizeof(char *));
    for (int i = 0; i < map.height; i++) {
        map.grid[i] = (char *)malloc(map.width * sizeof(char));
        fread(map.grid[i], sizeof(char), map.width, file); // Reading each row of the grid
    }

    fclose(file);

    // Displaying the map
    printf("Map dimensions: %dx%d\n", map.width, map.height);
    printf("Player position: (%d, %d)\n", map.p_x, map.p_y);
    printf("Map grid:\n");
    for (int i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            printf("%c", map.grid[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    freeMap(&map);

    return 0;
}
