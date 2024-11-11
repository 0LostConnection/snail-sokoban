#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "map.h"
#include "input.h"
#include "score.h"

void showMenu(int *levelUnlocked) {
    printf("### SOKOBAN ###\n");
    printf("Escolha a fase:\n");
    for (int i = 1; i <= *levelUnlocked; i++) {
        printf(" %d - Fase %d\n", i, i);
    }
    printf("Escolha a fase (1-%d): ", *levelUnlocked);
}

int main() {
    int levelUnlocked = loadScore(); // Carrega a última fase desbloqueada
    int choice;

    showMenu(&levelUnlocked);
    scanf("%d", &choice);

    if (choice < 1 || choice > levelUnlocked) {
        printf("Fase inválida.\n");
        return 1;
    }

    char mapFile[20];
    snprintf(mapFile, sizeof(mapFile), "fase%d.dat", choice);

    Map map;
    if (!loadMap(mapFile, &map)) {
        fprintf(stderr, "Erro ao carregar o mapa.\n");
        return 1;
    }

    Player player = findPlayer(&map);
    while (!isGameWon(&map)) {
        system("clear");
        printMap(&map, &player);

        char command = getUserInput();
        handleInput(command, &map, &player);
    }

    printf("Parabéns! Você completou a fase!\n");

    if (choice == levelUnlocked) {
        levelUnlocked++;
        saveScore(levelUnlocked); // Atualiza o nível desbloqueado
    }

    freeMap(&map);
    return 0;
}
