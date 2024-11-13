#include <stdio.h>

int main() {
    int width = 4, height = 4;
    int p_x = 2, p_y = 2;
    char grid[4][4] = {
        {'#', '#', '#', '#'},
        {'#', ' ', ' ', '#'},
        {'#', ' ', ' ', '#'},
        {'#', '#', '#', '#'},
    };

    FILE *file = fopen("fase1.dat", "wb");
    fwrite(&width, sizeof(int), 1, file);
    fwrite(&height, sizeof(int), 1, file);
    fwrite(&p_x, sizeof(int), 1, file);
    fwrite(&p_y, sizeof(int), 1, file);
    for (int i = 0; i < height; i++) {
        fwrite(grid[i], sizeof(char), width, file);
    }
    fclose(file);

    return 0;
}
