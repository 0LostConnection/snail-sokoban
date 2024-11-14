#include "../lib/command.h"

#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>

void move_player(Map map, Command d) {
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
        default: ;
    }
    if (map->grid[y][x] == BOX) {
        if (move_box(map, d, x, y)) {
            if (map->grid[map->player.posY][map->player.posX] != OPEN_GOAL) {
                map->grid[map->player.posY][map->player.posX] = NONE;
            }
            map->grid[y][x] = NONE;
            map->player.posX = x;
            map->player.posY = y;
        }
    } else if (map->grid[y][x] == CLOSED_GOAL) {
        if (move_star(map, d, x, y)) {
            map->grid[y][x] = OPEN_GOAL;
            map->player.posX = x;
            map->player.posY = y;
        }
    } else if (!hit_wall(map, d, x, y)) {
        map->player.posX = x;
        map->player.posY = y;
    }
    display_map(map);
}

Bool move_box(Map map, Command d, int x, int y) {
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
    if (!hit_wall(map, d, x, y) && !hit_box(map, d, x, y)) {
        if (map->grid[y][x] == OPEN_GOAL) {
            map->grid[y][x] = CLOSED_GOAL;
        } else {
            map->grid[y][x] = BOX;
        }
        return true;
    }
    return false;
}

Bool move_star(Map map, Command d, int x, int y) {
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
    if (!hit_wall(map, d, x, y)) {
        map->grid[y][x] = BOX;
        return true;
    }
    return false;
}

Bool hit_wall(Map map, Command d, int x, int y) {
    if (map->grid[y][x] == WALL) {
        return true;
    }
    return false;
}

Bool hit_box(Map map, Command d, int x, int y) {
    if (map->grid[y][x] == BOX) {
        return true;
    }
    return false;
}

Bool check_for_full_goal(Map map) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (map->grid[i][j] == OPEN_GOAL) {
                return false;
            }
        }
    }
    return true;
}

void end_game(char *msg) {
    clear_screen();

    int cols = 0;
    int rows = 0;
    get_cols_rows(&cols, &rows);
    move_cursor((int) ((cols - strlen(msg)) / 2), (int) rows / 2);

    printf("%s%s%s%s%s\n", BOLD, WHT_ON_RED, msg, TC_NRM, NORMAL);

    endwin();

    noecho();
    cbreak();
    getchar();
}
