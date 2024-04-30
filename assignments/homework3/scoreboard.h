#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <time.h>

extern time_t start_time, end_time;
void record_and_display_timer(const char *filename, time_t start_time, time_t end_time);
void save_game_time(const char *filename, time_t end_time);


#endif