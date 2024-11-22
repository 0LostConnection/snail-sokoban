#include <stdio.h>

#define HEIGHT 10
#define WIDTH 15
#define PLAYER_X 3
#define PLAYER_Y 3

int main() {
    char grid[HEIGHT][WIDTH] = {
        "###############",
        "#   #   O     #",
        "#   #   ###   #",
        "# P   C       #",
        "#   #######   #",
        "#       #     #",
        "#   C   #     #",
        "#   ### O   C #",
        "#   O         #",
        "###############"
    };

    FILE *file = fopen("sokoban.dat", "wb");

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
