#include <stdlib.h>

#include "externs.h"

/* Prepares the arrays and values backing the level */
level_t init_level(int width, int height)
{
	level_t level;

	level.width = width;
	level.height = height;

	int i, j;

	// Allocate/initialize terrain matrix */
	level.terrain = malloc(sizeof(char*) * height);
	char* terrainData = calloc(sizeof(char), width * height);
	for (i = 0; i < height; ++i)
		level.terrain[i] = &terrainData[i * width];

	// Allocate/initialize entity matrix
	level.mon_map = malloc(sizeof(monster_t**) * height);
	monster_t** monsterData = calloc(sizeof(monster_t*), width * height);
	for (i = 0; i < height; ++i)
		level.mon_map[i] = &monsterData[i * width];

	// Build terrain
	for (i = 0; i < width; ++i) {
		for (j = 0; j < height; ++j) {
			if (i > 0 && i < width - 1 && j > 0 && j < height - 1)
				level.terrain[i][j] = '.';
			else
				level.terrain[i][j] = '#';
		}
	}

	level.mon_list = NULL;

	return level;
}

/* Frees all dynamic memory held by the level */
void cleanup_level(level_t* level)
{
	free(level->terrain[0]);
	free(level->terrain);

	free(level->mon_map[0]);
	free(level->mon_map);

	monster_t* current = level->mon_list;
	while (current) {
		monster_t* next = current->next;
		free(current);
		current = next;
	}
}

/* Places a monster into the given level */
void add_monster(level_t* level, monster_t* monster)
{
	// Update back-pointer on current list head
	if (level->mon_list)
		level->mon_list->prev = monster;

	// Add monster to head of list and to monster map
	monster->next = level->mon_list;
	level->mon_list = monster;
	level->mon_map[monster->x][monster->y] = monster;
}

/* Removes a monster from the level, updating the monster list accordingly */
void rm_monster(level_t* level, monster_t* monster)
{
	if (monster->prev)
		monster->prev->next = monster->next;

	if (monster->next)
		monster->next->prev = monster->prev;

	// Head case
	if (level->mon_list == monster)
		level->mon_list = monster->next;

	// Remove map reference
	level->mon_map[monster->x][monster->y] = NULL;

	free(monster);
}
