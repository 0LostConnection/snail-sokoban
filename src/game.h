#ifndef GAME_H
#define GAME_H

#include "types.h"

Player findPlayer(Map *map);
void handleInput(char input, Map *map, Player *player);
int isGameWon(Map *map);

#endif
