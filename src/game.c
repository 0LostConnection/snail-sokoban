#include "game.h"

Player findPlayer(Map *map) {
    // Encontra a posição inicial do jogador no mapa
    Player player = {0, 0}; // Posição inicial fictícia (substituir pela lógica de busca)
    return player;
}

void handleInput(char input, Map *map, Player *player) {
    // Movimenta o jogador com base no comando e atualiza o mapa
    int newX = player->x, newY = player->y;
    switch (input) {
        case 'w': newY--; break; // Cima
        case 's': newY++; break; // Baixo
        case 'a': newX--; break; // Esquerda
        case 'd': newX++; break; // Direita
    }
    // Lógica para mover o jogador, incluindo verificação de colisões
}

int isGameWon(Map *map) {
    // Verifica se todas as caixas estão nos alvos
    return 0; // Retornar 1 se o jogador venceu
}
