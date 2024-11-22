#include <stdio.h>

#define HEIGHT 7
#define WIDTH 45
#define PLAYER_X -10
#define PLAYER_Y -10

int main() {
    char grid[HEIGHT][WIDTH] = {
        " ######   ##    ##     @@@     @@@@  ##      ",
        "##    ##  ###   ##    @@ @@     @@   ##      ",
        "##        ####  ##   @@   @@    @@   ##      ",
        " ######   ## ## ##  @@     @@   @@   ##      ",
        "      ##  ##  ####  @@@@@@@@@   @@   ##      ",
        "##    ##  ##   ###  @@     @@   @@   ##      ",
        " ######   ##    ##  @@     @@  @@@@  ########"
    };

    FILE *file = fopen("fase-1.dat", "wb");

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
