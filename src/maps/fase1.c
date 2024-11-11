#include <stdio.h>

int main() {
    int width = 7, height = 5;
    char grid[5][7] = {
        {'#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '@', ' ', '$', ' ', '#'},
        {'#', ' ', '.', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#'}
    };

    FILE *file = fopen("fase1.dat", "wb");
    fwrite(&width, sizeof(int), 1, file);
    fwrite(&height, sizeof(int), 1, file);
    for (int i = 0; i < height; i++) {
        fwrite(grid[i], sizeof(char), width, file);
    }
    fclose(file);

    return 0;
}