#include "input.h"
#include <stdio.h>

char getUserInput() {
    char input;
    printf("Use W (cima), A (esquerda), S (baixo), D (direita) para mover: ");
    scanf(" %c", &input);
    return input;
}
