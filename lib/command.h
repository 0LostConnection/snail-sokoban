#ifndef OPERATION_H
#define OPERATION_H

#include "map.h"
#include "player.h"
#include "base.h"

void move_player(Map map, Command d);

Bool move_box(Map map, Command d, int x, int y);

Bool hit_wall(Map map, Command d, int x, int y);

Bool hit_box(Map map, Command d, int x, int y);

Bool move_star(Map map, Command d, int x, int y);

Bool check_for_full_goal(Map map);

void end_game(char *msg);

#endif
