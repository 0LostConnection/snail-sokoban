#include "../lib/operation.h"

void movePlayer(Map map, Command d) {
    int x = map->player.posX;
    int y = map->player.posY;

    switch (d) {
        case UP:
            y--;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case DOWN:
            y++;
            break;
    }
}
