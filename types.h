/* Global type declarations */

#ifndef TYPES_H
#define TYPES_H

typedef struct player_t
{
	char symbol;
	int x;
	int y;
	int hp;
	int max_hp;
} player_t;

typedef struct monster_t
{
	char symbol;
	int x;
	int y;
	int hp;
	// Used to build linked list of all monsters in a level
	struct monster_t* next;
	struct monster_t* prev;
} monster_t;

typedef struct level_t
{
	int width;
	int height;
	char diff;
	char** terrain; // 2D array of chars
	monster_t*** mon_map; // 2D array of monster_t*
	monster_t* mon_list; // List of all living monsters
} level_t;

#endif
