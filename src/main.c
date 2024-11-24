#include "../lib/base.h"
#include "../lib/command.h"
#include "../lib/map.h"
#include "../lib/score.h"

#include <ncurses/ncurses.h>
#include <stdio.h>
#include <string.h>

int main() {
    Bool quit_game = false;

    while (!quit_game) {
        clear_screen();
        show_cursor(false);

        LEVELS current_level = TITLE_LEVEL;
        Bool quit_level = false;
        char input;
        Map map = init_map(current_level);
        int cols = 0;
        int rows = 0;

        // MENU INICIAL
        initscr(); // inicia o ncurses
        cbreak(); // permite a entrada do teclado sem o enter
        noecho(); // oculta a entrada do teclado
        timeout(-1); // Espera a entrada do usuário para sempre

        print_header("Bem-Vindo(a)!", cols, rows);

        display_map(map);

        LEVELS score = load_score();
        char title_footer[100];

        switch (score) {
            case TITLE_LEVEL:
                strcpy(title_footer, "Pressione qualquer tecla para iniciar");
                break;
            case MAX_LEVEL:
                strcpy(title_footer, "Voce venceu! Pressione [c] para apagar os dados");
                break;
            default:
                sprintf(title_footer, "Voce conseguiu ate a fase %d! Pressione [c] para apagar os dados", score + 1);
                break;
        }

        print_footer(title_footer, cols, rows, map->height);

        endwin();

        noecho();
        cbreak();
        input = getchar();

        //Input para escolher o mapa.
        //Fiz a correção do input, não estava sendo possível escolher o mapa 10.
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
            case '6':
                current_level = SIXTH_LEVEL;
                break;
            case '7':
                current_level = SEVENTH_LEVEL;
                break;
            case '8':
                current_level = EIGHT_LEVEL;
                break;
            case '9':
                current_level = NINE_LEVEL;
                break;
            case '0':
                current_level = TENTH_LEVEL;
                break;
            case CLEAR:
                score = TITLE_LEVEL;
                save_score(score);
                current_level = FIRST_LEVEL;
                break;
            case QUIT:
                quit_game = true;
                continue;
            default:
                current_level = FIRST_LEVEL;
                break;
        }

        clear_screen();

        map = init_map(current_level);
        if (!map) {
            printf("Erro ao carregar o mapa.\n");
            quit_game = true;
            continue;
        }

        // LOOP DO JOGO
        while (!quit_level && !quit_game) {
            initscr();
            cbreak();
            noecho();
            timeout(-1);

            display_map(map);

            char level_header[20];
            sprintf(level_header, "Level %d", current_level + 1);
            print_header(level_header, cols, rows);

            char level_footer[100];
            sprintf(level_footer, "Maximo: %d", score + 1);
            print_footer(level_footer, cols, rows, map->height);

            input = getchar();
            endwin();

            switch (input) {
                case UP:
                    move_player(map, UP);
                    break;
                case LEFT:
                    move_player(map, LEFT);
                    break;
                case DOWN:
                    move_player(map, DOWN);
                    break;
                case RIGHT:
                    move_player(map, RIGHT);
                    break;
                case RESTART:
                    free_map(map);
                    map = init_map(current_level);
                    break;
                case QUIT:
                    quit_level = true;
                    break;
                case BACK_TO_MENU: // Defina BACK_TO_MENU como a tecla desejada para voltar ao menu
                    quit_level = true;
                    break;
                default:
                    break;
            }

            if (!quit_level && check_for_full_goal(map)) {
                score = current_level;
                save_score(score);

                current_level++;

                if (current_level > MAX_LEVEL) {
                    end_game("You Win!");
                    quit_level = true;
                } else {
                    free_map(map);
                    map = init_map(current_level);
                }
            }
        }

        free_map(map);
    }

    endwin();
    return 0;
}
