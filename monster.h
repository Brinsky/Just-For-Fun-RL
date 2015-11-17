#ifndef MONSTER_H
#define MONSTER_H

#include "player.h"
#include "stats.h"

// Forward declaration to avoid circular dependency
typedef struct Player Player;

typedef struct Monster
{
	char symbol;
	Stats stats;
	int x;
	int y;
	// Used to build linked list of all monsters in a level
	struct Monster* next;
	struct Monster* prev;
} Monster;

Monster* alloc_monster(char, int, int, int);
void monster_turn(Monster*, Level*, Player*);
void hit_monster(Monster*, Level*, Player*);

#endif
