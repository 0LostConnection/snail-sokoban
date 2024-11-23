#include "../lib/base.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void clear_screen() {
    system("cls");
}

void move_cursor(int x, int y) {
    do {
        COORD coord = {x, y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    } while (0);
}

void get_cols_rows(int *cols, int *rows) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    
    *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void print_header(char *message, int cols, int rows) {
    get_cols_rows(&cols, &rows);
    move_cursor((int) ((cols - strlen(message)) / 2), (int) rows / 4);
    printf("%s%s%s%s%s", BOLD, WHT_ON_RED, message, TC_NRM, NORMAL);
}

void print_footer(char *message, int cols, int rows, int map_height) {
    get_cols_rows(&cols, &rows);
    move_cursor(((int) (cols - strlen(message)) / 2), rows / 4 + map_height + 5);
    printf("%s%s%s%s%s", BOLD, WHT_ON_RED, message, TC_NRM, NORMAL);
}

void show_cursor(bool flag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = flag;
    SetConsoleCursorInfo(out, &cursorInfo);
}
