#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include "monster.h"
#include "player.h"

typedef enum
{
	/* Creatures class */
	CREATURE_START,
	PLAYER,
	MONSTER,
	CREATURE_END,

	/* Mechanisms class */
	MECHANISM_START,
	DOOR,
	TRAP,
	CHEST,
	MECHANISM_END,
	
	/* Items class */
	ITEM
} EntityType;

typedef struct Entity
{
	const EntityType type;
	const void* entity;
	struct Entity* below; // Used for entity stacking in a level
} Entity;

// Entity creation functions
Entity* monster_to_entity(Entity*, Monster*);
Entity* player_to_entity(Entity*, Player*);

// Entity test functions
bool is_item(Entity* entity);
bool is_mechanism(Entity* entity);
bool is_creature(Entity* entity);

// Entity cast functions
Monster* get_monster(Entity* entity);
Player* get_player(Entity* entity);

#endif
