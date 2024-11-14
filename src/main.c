#include "../lib/base.h"
#include "../lib/map.h"
#include "../lib/command.h"
#include "../lib/score.h"

#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>

int main() {
    clear_screen();

    LEVELS current_level = TITLE_LEVEL;
    Bool quit = false;
    char input;
    Map map = init_map(current_level);
    int cols = 0;
    int rows = 0;

    initscr();
    cbreak();
    noecho();
    timeout(-1);

    get_cols_rows(&cols, &rows);
    char msg[100] = "Bem-Vindo(a)!";
    move_cursor((int) ((cols - strlen(msg)) / 2), (int) rows / 4);
    printf("%s%s%s%s%s", BOLD, WHT_ON_RED, msg, TC_NRM, NORMAL);

    display_map(map);

    LEVELS score = load_score();

    sprintf(msg, "Voce parou na fase %d! Pressione [c] para apagar os dados", score);

    get_cols_rows(&cols, &rows);
    move_cursor(((int) (cols - strlen(msg)) / 2), rows / 4 + map->height + 4);
    printf("%s%s%s%s%s", BOLD, WHT_ON_RED, msg, TC_NRM, NORMAL);

    endwin();

    noecho();
    cbreak();
    input = getchar();

    switch (input) {
        case '1':
            current_level = FIRST_LEVEL;
            break;
        case '2':
            current_level = SECOND_LEVEL;
            break;
        case '3':
            current_level = THIRD_LEVEL;
            break;
        case '4':
            current_level = FOURTH_LEVEL;
            break;
        case '5':
            current_level = FIFTH_LEVEL;
            break;
        case 'c':
            save_score(FIRST_LEVEL);
            current_level = FIRST_LEVEL;
            break;
        default:
            current_level = score;
            break;
    }

    clear_screen();
    map = init_map(current_level);

    while (!quit) {
        initscr();
        cbreak();
        noecho();
        timeout(-1);

        display_map(map);

        char level_title[20];
        sprintf(level_title, "Level %d", current_level);

        strcpy(msg, level_title);

        get_cols_rows(&cols, &rows);
        move_cursor((int) ((cols - strlen(msg)) / 2), (int) rows / 4);
        printf("%s%s%s%s%s", BOLD, WHT_ON_RED, msg, TC_NRM, NORMAL);

        input = getchar();
        endwin();

        clear_screen();

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
                free_map(map);
                map = init_map(current_level);
                if (map == NULL) {
                    // Verificação para garantir que o mapa foi carregado
                    quit = true;
                    printf("Erro ao reiniciar a fase. Encerrando...\n");
                } else {
                    display_map(map);
                    printf("Restart\n");
                }
                endwin();
                break;
            default:
                endwin();
                break;
        }

        if (!quit && check_for_full_goal(map)) {
            current_level++;

            if (current_level > MAX_LEVEL) {
                end_game("You Win!");
                free_map(map);
                break;
            }

            score = current_level;
            save_score(score);

            clear_screen();
            char next_level_question[] =
                    "Voce venceu! Deseja ir para a proxima fase ou sair? [q]";

            move_cursor((int) ((cols - strlen(next_level_question)) / 2), (int) rows / 4);
            printf("%s%s%s%s%s\n", BOLD, WHT_ON_RED, next_level_question, TC_NRM, NORMAL);

            endwin();

            noecho();
            cbreak();
            input = getchar();

            if (input != 'q') {
                clear_screen();

                move_cursor((int) ((cols - strlen(msg)) / 2), (int) rows / 4);
                printf("%s%s%s%s%s\n", BOLD, WHT_ON_RED, msg, TC_NRM, NORMAL);

                map = init_map(current_level);
                display_map(map);

                endwin();
            } else {
                quit = true;
                free_map(map);
                endwin();
            }
        }
    }

    endwin();
    return 0;
}
