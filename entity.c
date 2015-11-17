#include <assert.h>
#include <string.h>
#include "entity.h"

/* Initialize a given Entity struct with the requested fields.
 * This function should not be publicly exposed.
 */
Entity* init_entity(Entity* entity, EntityType type, void* child, Entity* below)
{
	assert(entity && child);

	// Slight hack to get around const-ness of Entity struct members
	Entity temp = { .type = type, .entity = child, .below = below };
	return memcpy(entity, &temp, sizeof(Entity));
}

/* Initializes the given Entity struct to encompass the given Monster.
 * Returns a pointer to `entity`.
 */
Entity* monster_to_entity(Entity* entity, Monster* monster)
{
	return init_entity(entity, MONSTER, monster, NULL);
}

/* Initializes the given Entity struct to encompass the given Player.
 * Returns a pointer to `entity`.
 */
Entity* player_to_entity(Entity* entity, Player* player)
{
	return init_entity(entity, PLAYER, player, NULL);
}

/* Tests if a given Entity is an ITEM */
bool is_item(Entity* entity)
{
	return entity && entity->type == ITEM;
}

/* Tests if a given Entity is a MECHANISM */
bool is_mechanism(Entity* entity)
{
	return entity && entity->type > MECHANISM_START && entity->type < MECHANISM_END;
}

/* Tests if a given Entity is a CREATURE */
bool is_creature(Entity* entity)
{
	return entity && entity->type > CREATURE_START && entity->type < CREATURE_END;
}

/* Casts a given Entity to a Monster*. The Entity pointer and it's contained
 * child pointer MUST be non-NULL. You should be certain that the type field of
 * `entity` contains MONSTER before calling this function.
 */
Monster* get_monster(Entity* entity)
{
	assert(entity && entity->type == MONSTER && entity->entity);

	return (Monster*) entity->entity;
}

/* Casts a given Entity to a Monster*. The Entity pointer and it's contained
 * child pointer MUST be non-NULL. You should be certain that the type field of
 * `entity` contains MONSTER before calling this function.
 */
Player* get_player(Entity* entity)
{
	assert(entity && entity->type == PLAYER && entity->entity);

	return (Player*) entity->entity;
}
