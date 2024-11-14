#include "../lib/score.h"
#include "../lib/base.h"

#include <stdio.h>
#include <stdlib.h>

int load_score() {
    LEVELS unlocked_level;
    FILE *score_file = fopen("score.dat", "rb");

    if (score_file == NULL) {
        fclose(score_file);
        save_score(FIRST_LEVEL);
        unlocked_level = FIRST_LEVEL;
    }

    fread(&unlocked_level, sizeof(int), 1, score_file);
    fclose(score_file);

    return unlocked_level;
}

void save_score(LEVELS unlocked_level) {
    FILE *score_file = fopen("score.dat", "wb");

    if (score_file) {
        fwrite(&unlocked_level, sizeof(int), 1, score_file);
        fclose(score_file);
    }
}
