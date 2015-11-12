#include <stdbool.h>

#include "types.h"

#ifndef EXTERNS_H
#define EXTERNS_H

extern log_t turn_log;

/* Log-related functions */
void init_log();
void write_log(char*);
void clear_log();

/* Level-related functions */
level_t init_level(int, int);
void cleanup_level(level_t*);
void add_monster(level_t*, monster_t*);
void rm_monster(level_t*, monster_t*);
bool is_open(level_t*, int, int);

/* Monster-related functions */
monster_t* alloc_monster(char, int, int, int);
void monster_turn(monster_t*, level_t*, player_t*);
void hit_monster(monster_t*, level_t*, player_t*);

/* Player-related functions */
player_t init_player(char, int, int, int);
void attempt_act(level_t*, player_t*, int, int);

#endif
