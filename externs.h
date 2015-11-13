#include <stdbool.h>

#include "types.h"

#ifndef EXTERNS_H
#define EXTERNS_H

/* Log-related functions */
void writef_log(char*, ...);
void write_log(char*);
void clear_log();
void log_next_line();
void log_prev_line();
int log_pos();
int log_line();
int log_total_lines();
char log_at(int);

/* Level-related functions */
level_t init_level(int, int);
void cleanup_level(level_t*);
void add_monster(level_t*, monster_t*);
void rm_monster(level_t*, monster_t*);
bool is_open(level_t*, int, int);

/* Stats-related functions */
stats_t init_stats(int, int, int, int, int, int);
int attack(stats_t*, stats_t*);

/* Monster-related functions */
monster_t* alloc_monster(char, int, int, int);
void monster_turn(monster_t*, level_t*, player_t*);
void hit_monster(monster_t*, level_t*, player_t*);

/* Player-related functions */
player_t init_player(char, int, int, int);
void attempt_act(level_t*, player_t*, int, int);

#endif
