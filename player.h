#ifndef PLAYER_H
#define PLAYER_H

#include "level.h"
#include "stats.h"

typedef struct Player
{
	char symbol;
	Stats stats;
	int x;
	int y;
} Player;

Player init_player(char, int, int, int);
void attempt_act(Level*, Player*, int, int);

#endif
