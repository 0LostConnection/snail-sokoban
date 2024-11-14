#include <stdio.h>

#define HEIGHT 6
#define WIDTH 7
#define PLAYER_X 2
#define PLAYER_Y 2

int main() {
    char grid[HEIGHT][WIDTH] = {
        {'#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', 'x', 'o', ' ', '#'},
        {'#', ' ', ' ', 'x', 'o', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#'}
    };

    FILE *file = fopen("fase3.dat", "wb");

    const int width = WIDTH;
    const int height = HEIGHT;
    const int playerX = PLAYER_X;
    const int playerY = PLAYER_Y;

    fwrite(&width, sizeof(int), 1, file);
    fwrite(&height, sizeof(int), 1, file);
    fwrite(&playerX, sizeof(int), 1, file);
    fwrite(&playerY, sizeof(int), 1, file);

    fwrite(grid, sizeof(char), width * height, file);

    fclose(file);

    return 0;
}
