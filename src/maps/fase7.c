#include <stdio.h>

#define HEIGHT 15
#define WIDTH 39
#define PLAYER_X 4
#define PLAYER_Y 7

int main() {
    char grid[HEIGHT][WIDTH] = {
    "#######################################",
    "#######################################",
    "##     o     ##   x       o          ##",
    "##    #####  ##       #######        ##",
    "##   ##   ##    x    ##             ##",
    "## x ## x #######       ##          ##",
    "##    ##    o  ##  x    ##    o     ##",
    "######    x    ##       ##   ####   ##",
    "##     ##########  ######  x ##     ##",
    "##   o #########   ##         ##    ##",
    "## x         ##    ##    x    ##    ##",
    "##     o     ##    ######     ## o  ##",
    "##  #######        ######     ##    ##",
    "#######################################",
    "#######################################"
    };

    FILE *file = fopen("fase7.dat", "wb");

    const int width = WIDTH;
    const int height = HEIGHT;
    const int playerX = PLAYER_X;
    const int playerY = PLAYER_Y;

    fwrite(&width, sizeof(int), 1, file);
    fwrite(&height, sizeof(int), 1, file);
    fwrite(&playerX, sizeof(int), 1, file);
    fwrite(&playerY, sizeof(int), 1, file);

    for (int i = 0; i < HEIGHT; i++) {
        fwrite(grid[i], sizeof(char), WIDTH, file);
    }

    fclose(file);

    return 0;
}
