#ifndef PLAYER_HEADER
#define PLAYER_HEADER

typedef struct player{
    int posX;
    int posY;
} Player;

typedef enum Command{
    UP = 'w', ///< w: up
    LEFT = 'a', ///< a: left
    DOWN = 's', ///< s: down
    RIGHT = 'd', ///< d: right
    RESTART = 'r', ///< r: restart
    QUIT = 'q' ///< q: quit
} Command;


#endif