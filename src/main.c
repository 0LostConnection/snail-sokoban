#include "../lib/base.h"
#include "../lib/map.h"
#include "../lib/command.h"

#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>

int main() {
    clear_screen();

    Bool quit = false;
    char input;
    Map map = init_map("fase1.dat");
    int cols = 0;
    int rows = 0;

    initscr();
    cbreak();
    noecho();
    timeout(-1);

    get_cols_rows(&cols, &rows);
    char msg[100] = "Welcome!";
    move_cursor((int) ((cols - strlen(msg)) / 2), (int) rows / 4);
    printf("%s%s%s%s%s", BOLD, WHT_ON_RED, msg, TC_NRM, NORMAL);
    display_map(map);

    endwin();

    while (!quit) {
        initscr();
        cbreak();
        noecho();
        timeout(-1);

        display_map(map);

        input = getchar();
        endwin();
        clear_screen();

        strcpy(msg, "Fase 1");
        get_cols_rows(&cols, &rows);
        move_cursor((int) ((cols - strlen(msg)) / 2), (int) rows / 4);
        printf("%s%s%s%s%s", BOLD, WHT_ON_RED, msg, TC_NRM, NORMAL);
        display_map(map);

        switch (input) {
            case UP:
                printf("Moving up\n");
                move_player(map, UP);
                endwin();
                break;
            case LEFT:
                printf("Moving left\n");
                move_player(map, LEFT);
                endwin();
                break;
            case DOWN:
                printf("Moving down\n");
                move_player(map, DOWN);
                endwin();
                break;
            case RIGHT:
                printf("Moving right\n");
                move_player(map, RIGHT);
                endwin();
                break;
            case 'q':
                quit = true;
                printf("Quit\n");
                endwin();
                break;
            case 'r':
                map = init_map("level1.dat");
                display_map(map);
                printf("Restart\n");
                endwin();
                break;
            default:
                endwin();
                break;
        }

        if (!quit && check_for_full_goal(map)) {
            end_game("You Win!");
            break;
        }
    }
    endwin();
    return 0;
}
