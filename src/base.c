#include "../lib/base.h"

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