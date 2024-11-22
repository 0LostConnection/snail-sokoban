#include <stdio.h>

#define HEIGHT 15
#define WIDTH 30
#define PLAYER_X 6
#define PLAYER_Y 6

int main() {
    char grid[HEIGHT][WIDTH] = {
        "##############################",
        "##       ##        ##       ##",
        "##   x   ##   o x  ##   x   ##",
        "##       ##        ##       ##",
        "##   o   ####   x  ####   o ##",
        "####     ####   o  ####     ##",
        "##       ##        ##       ##",
        "##   x   ##   o    ##       ##",
        "##       ####   x  ####       ",
        "##   o              o   x   ##",
        "##############################"
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
