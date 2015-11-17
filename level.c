#include <stdlib.h>

#include "level.h"
#include "monster.h"

/* Prepares the arrays and values backing the level */
Level init_level(int width, int height)
{
	// Allocate/initialize terrain matrix */
	char** terrain = malloc(sizeof(char*) * height);
	char* terrainData = calloc(sizeof(char), width * height);
	for (int i = 0; i < height; ++i)
		terrain[i] = &terrainData[i * width];

	// Allocate/initialize entity matrix
	Entity*** entity_map = malloc(sizeof(Entity**) * height);
	Entity** entityData = calloc(sizeof(Entity*), width * height);
	for (int i = 0; i < height; ++i)
		entity_map[i] = &entityData[i * width];

	// Allocate/initialize entity matrix
	Monster*** mon_map = malloc(sizeof(Monster**) * height);
	Monster** monsterData = calloc(sizeof(Monster*), width * height);
	for (int i = 0; i < height; ++i)
		mon_map[i] = &monsterData[i * width];

	// Build terrain
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (i > 0 && i < width - 1 && j > 0 && j < height - 1)
				terrain[i][j] = '.';
			else
				terrain[i][j] = '#';
		}
	}

	Level level =
	{
		.width = width,
		.height = height,
		.terrain = terrain,
		.entity_map = entity_map,
		.mon_map = mon_map,
		.mon_list = NULL
	};

	return level;
}

/* Frees all dynamic memory held by the level */
void cleanup_level(Level* level)
{
	free(level->terrain[0]);
	free(level->terrain);

	free(level->entity_map[0]);
	free(level->entity_map);

	free(level->mon_map[0]);
	free(level->mon_map);

	Monster* current = level->mon_list;
	while (current) {
		Monster* next = current->next;
		free(current);
		current = next;
	}
}

/* Places a monster into the given level */
void add_monster(Level* level, Monster* monster)
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
void rm_monster(Level* level, Monster* monster)
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

/* Checks if a position can be moved into by an actor */
bool is_open(Level* level, int x, int y)
{
	return x >= 0 && x < level->width && y >= 0 && y < level->height
		&& level->terrain[x][y] == '.' && level->mon_map[x][y] == NULL;
}

bool in_bounds(Level* level, int x, int y)
{
	return x >= 0 && x < level->width && y >= 0 && y < level->height;
}

/* Returns true if the given position is in bounds and contains an Entity of
 * type CREATURE.
 */
bool has_creature(Level* level, int x, int y)
{
	return in_bounds(level, x, y) && level->entity_map[x][y]
			&& is_creature(level->entity_map->type);
}

/* Returns true if the given position is in bounds and contains an Entity of
 * type MECHANISM.
 */
bool has_mechanism(Level* level, int x, int y)
{
	/* If the Entity stack at a given position contains a mechanism, it
	 * will be either the top element or the element after that
	 */
	if (in_bounds(level, x, y)) {
		Entity* entity = level->entity_map[x][y];

		return (entity && is_mechanism(entity))
			|| (entity->below && is_mechanism(entity->below));
	}

	return false;
}

/* Returns true if the given position is in bounds and contains an Entity of
 * type ITEM.
 */
bool has_item(Level* level, int x, int y)
{
	/* If the Entity stack at a given position contains any items, one of
	 * them will be in the first 3 elements of the stack
	 */
	if (in_bounds(level, x, y)) {
		Entity* entity = level->entity_map[x][y];

		return (entity && is_item(entity))
			|| (entity->below && is_item(entity->below))
			|| (entity->below->below && is_item(entity->below->below));
	}

	return false;
}
