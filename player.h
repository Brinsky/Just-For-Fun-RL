#ifndef PLAYER_H
#define PLAYER_H

#include "level.h"
#include "stats.h"

typedef struct player_t
{
	char symbol;
	stats_t stats;
	int x;
	int y;
} player_t;

player_t init_player(char, int, int, int);
void attempt_act(level_t*, player_t*, int, int);

#endif
