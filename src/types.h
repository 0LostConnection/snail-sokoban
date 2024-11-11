#ifndef TYPES_H
#define TYPES_H

typedef struct {
    int x;
    int y;
} Player;

typedef struct {
    char **grid;
    int width;
    int height;
} Map;

#endif
