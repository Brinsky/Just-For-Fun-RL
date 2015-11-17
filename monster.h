#ifndef MONSTER_H
#define MONSTER_H

#include "player.h"
#include "stats.h"

// Forward declaration to avoid circular dependency
typedef struct player_t player_t;

typedef struct monster_t
{
	char symbol;
	stats_t stats;
	int x;
	int y;
	// Used to build linked list of all monsters in a level
	struct monster_t* next;
	struct monster_t* prev;
} monster_t;

monster_t* alloc_monster(char, int, int, int);
void monster_turn(monster_t*, level_t*, player_t*);
void hit_monster(monster_t*, level_t*, player_t*);

#endif
