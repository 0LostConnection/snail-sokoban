#ifndef BASE_H
#define BASE_H

#include <stdbool.h>

#define Bool bool

typedef enum LEVELS {
    TITLE_LEVEL = -1,
    FIRST_LEVEL = 0,
    SECOND_LEVEL = 1,
    THIRD_LEVEL = 2,
    FOURTH_LEVEL = 3,
    FIFTH_LEVEL = 4,
    SIXTH_LEVEL = 5,
    SEVENTH_LEVEL = 6,
    EIGHT_LEVEL = 7,
    NINE_LEVEL = 8,
    TENTH_LEVEL = 9,
    MAX_LEVEL = 9
} LEVELS;


typedef enum Command {
    UP = 'w',
    LEFT = 'a',
    DOWN = 's',
    RIGHT = 'd',
    RESTART = 'r',
    QUIT = 'q',
    CLEAR = 'c',
    CONTINUE = 'w',
    BACK_TO_MENU = 'm'
} Command;

#define TC_NRM  "\033[0m"
#define TC_RED  "\033[1;31m"
#define TC_GRN  "\033[1;32m"
#define TC_YEL  "\033[1;33m"
#define TC_BLU  "\033[1;34m"
#define TC_MAG  "\033[1;35m"
#define TC_CYN  "\033[1;36m"
#define TC_WHT  "\033[1;37m"


#define BOLD "\033[1m"
#define NORMAL "\033[0m"

#define YEL_ON_BLU "\033[33;44m"
#define MAG_ON_WHT "\033[35;47m"
#define MAG_ON_CYN "\033[35;46m"
#define WHT_ON_RED "\033[37;41m"

#define TC_BG_NRM "\x1B[40m"
#define TC_BG_RED "\x1B[41m"
#define TC_BG_GRN "\x1B[42m"
#define TC_BG_YEL "\x1B[43m"
#define TC_BG_BLU "\x1B[44m"
#define TC_BG_MAG "\x1B[45m"
#define TC_BG_CYN "\x1B[46m"
#define TC_BG_WHT "\x1B[47m"

// Limpa a tela no Windows
void clear_screen();

// Função para mover o cursor no console do Windows
void move_cursor(int x, int y);

// Função para obter tamanho do terminal no Windows
void get_cols_rows(int *cols, int *rows);

// Função para imprimir o título
void print_header(char *message, int cols, int rows);

// Função para imprimir o rodapé
void print_footer(char *message, int cols, int rows, int map_height);

// Função para ativar/desativar o cursor
void show_cursor(bool flag);

#endif
