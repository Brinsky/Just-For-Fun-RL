#ifndef LEVEL_H
#define LEVEL_H

#include <stdbool.h>
#include "entity.h"

// Forward declaration to avoid circular dependency
typedef struct Monster Monster;

typedef struct Level
{
	const int width;
	const int height;
	char** terrain; // 2D array of chars
	Entity*** entity_map;
	Monster*** mon_map; // 2D array of Monster*
	Monster* mon_list; // List of all living monsters
} Level;

Level init_level(int, int);
void cleanup_level(Level*);
void add_monster(Level*, Monster*);
void rm_monster(Level*, Monster*);
bool is_open(Level*, int, int);

bool is_open(Level*, int, int);

bool has_creature(Level*, int, int);
bool has_mechanism(Level*, int, int);
bool has_item(Level*, int, int);

#endif
