#include <stdio.h>
#include <time.h>
#include "scoreboard.h"

time_t start_time, end_time;
double game_time;

void save_game_time(const char *filename, time_t end_time) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }
    fprintf(fp, "%f\n", game_time);
    fclose(fp);
}

void record_and_display_timer(const char *filename, time_t start_time, time_t end_time) {
    printf("Start Time: %s", ctime(&start_time));
    printf("End Time: %s", ctime(&end_time));


    game_time = difftime(end_time, start_time);
    save_game_time(filename,game_time);
    printf("Game Time: %f seconds\n", game_time);
    }
