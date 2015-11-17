#ifndef LEVEL_H
#define LEVEL_H

#include <stdbool.h>

// Forward declaration to avoid circular dependency
typedef struct monster_t monster_t;

typedef struct level_t
{
	int width;
	int height;
	char** terrain; // 2D array of chars
	monster_t*** mon_map; // 2D array of monster_t*
	monster_t* mon_list; // List of all living monsters
} level_t;

/* Level-related functions */
level_t init_level(int, int);
void cleanup_level(level_t*);
void add_monster(level_t*, monster_t*);
void rm_monster(level_t*, monster_t*);
bool is_open(level_t*, int, int);

#endif
