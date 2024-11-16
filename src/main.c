#include "../lib/base.h"
#include "../lib/map.h"
#include "../lib/command.h"
#include "../lib/score.h"

#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>

int main() {
    clear_screen();
    show_cursor(false);

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

    print_header("Bem-Vindo(a)!", cols, rows);

    display_map(map);

    LEVELS score = load_score();
    LEVELS old_score = score;

    char title_footer[100];
    sprintf(title_footer, "Voce conseguiu ate a fase %d! Pressione [c] para apagar os dados", score);
    print_footer(title_footer, cols, rows, map->height);

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
        case 'w':
            current_level = score;
            break;
        default:
            current_level = FIRST_LEVEL;
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

        char level_header[20];
        sprintf(level_header, "Level %d", current_level);
        print_header(level_header, cols, rows);

        char level_footer[100];
        sprintf(level_footer, "Maximo: %d", old_score);
        print_footer(level_footer, cols, rows, map->height);

        input = getchar();
        endwin();

        //clear_screen();
        display_map(map);

        switch (input) {
            case UP:
                move_player(map, UP);
                endwin();
                break;
            case LEFT:
                move_player(map, LEFT);
                endwin();
                break;
            case DOWN:
                move_player(map, DOWN);
                endwin();
                break;
            case RIGHT:
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
                }
                endwin();
                break;
            default:
                endwin();
                break;
        }

        if (!quit && check_for_full_goal(map)) {
            score = current_level;
            save_score(score);

            current_level++;

            if (current_level > MAX_LEVEL) {
                end_game("You Win!");
                free_map(map);
                break;
            }


            clear_screen();

            print_header("Voce venceu! Deseja ir para a proxima fase ou sair? [q]", cols, rows);

            endwin();

            noecho();
            cbreak();
            input = getchar();

            if (input != 'q') {
                clear_screen();

                sprintf(level_header, "Level %d", current_level);
                print_header(level_header, cols, rows);

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
