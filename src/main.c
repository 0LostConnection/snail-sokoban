#include "../lib/base.h"
#include "../lib/map.h"
#include "../lib/operation.h"

#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>

int main() {
    clear_screen();
    Bool quit = false;
    char input;

    Map map = initMap("fase1.dat");
    int cols = 0;
    int rows = 0;
    tc_get_cols_rows(&cols, &rows);
    char msg[100] = "Welcome!";
    tc_move_cursor((int)((cols - strlen(msg)) / 2), (int)rows / 4);
    printf("%s%s%s%s%s\n", BOLD, WHT_ON_RED, msg, TC_NRM, NORMAL);
    display_map(map);

    while (!quit) {
        initscr();
        noecho();
        cbreak();
        timeout(-1);

        input = getchar();
        endwin();
        clear_screen();

        strcpy(msg, "Fase 1");

        tc_move_cursor((int)((cols - strlen(msg)) / 2), (int)rows / 4);
        printf("%s%s%s%s%s\n", BOLD, WHT_ON_RED, msg, TC_NRM, NORMAL);
        display_map(map);

        switch (input) {
            case UP:
                printf("Moving up\n");
                movePlayer(map, UP);
                endwin();
                break;
            case LEFT:
                printf("Moving left\n");
                movePlayer(map, LEFT);
                endwin();
                break;
            case DOWN:
                printf("Moving down\n");
                movePlayer(map, DOWN);
                endwin();
                break;
            case RIGHT:
                printf("Moving right\n");
                movePlayer(map, RIGHT);
                endwin();
                break;
            case 'q':
                quit = true;
                printf("Quit\n");
                endwin();
                break;
            case 'r':
                map = initMap("level1.dat");
                display_map(map);
                printf("Restart\n");
                endwin();
                break;
            default:
                endwin();
                break;
        }
    }
}
