#include "score.h"
#include <stdio.h>

int loadScore() {
    FILE *file = fopen("score.dat", "rb");
    int score = 1;
    if (file) {
        fread(&score, sizeof(int), 1, file);
        fclose(file);
    }
    return score;
}

void saveScore(int score) {
    FILE *file = fopen("score.dat", "wb");
    if (file) {
        fwrite(&score, sizeof(int), 1, file);
        fclose(file);
    }
}
