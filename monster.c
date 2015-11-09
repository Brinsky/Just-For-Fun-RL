#include <stdlib.h>

#include "externs.h"
#include "types.h"

monster_t* alloc_monster(char symbol, int x, int y, int hp)
{
	monster_t* monster = malloc(sizeof(monster_t));
	monster->symbol = symbol;
	monster->x = x;
	monster->y = y;
	monster->hp = hp;

	monster->next = NULL;
	monster->prev = NULL;

	return monster;
}

void attempt_move(monster_t* monster, level_t* level, player_t* player, int x, int y)
{
	if (x >= 0 && x < level->width && y >= 0 && y < level->height
			&& level->terrain[x][y] == '.'
			&& level->mon_map[x][y] == NULL
			&& !(x == player->x && y == player->y)) {
		level->mon_map[monster->x][monster->y] = NULL;
		monster->x = x;
		monster->y = y;
		level->mon_map[x][y] = monster;	
	}
}

/* Process a monster's turn */
void monster_turn(monster_t* monster, level_t* level, player_t* player)
{
	int distX = monster->x - player->x;
	int distY = monster->y - player->y;

	// Attack the player if close enough
	if (distX >= -1 && distX <= 1 && distY >= -1 && distY <= 1) {
		player->hp--;
		write_log("The monster hits you.");
	} else { // Otherwise move towards them
		int x = 0;
		if (distX > 0)
			x = -1;
		else if (distX < 0)
			x = 1;

		int y = 0;
		if (distY > 0)
			y = -1;
		else if (distY < 0)
			y = 1;

		attempt_move(monster, level, player, monster->x + x, monster->y + y);
	}
}

/* Process a player v. monster attack */
void hit_monster(monster_t* monster, level_t* level, player_t* player)
{
	monster->hp -= 5;

	if (monster->hp <= 0) {
		rm_monster(level, monster);
		write_log("You kill the monster.");
	} else {
		write_log("You strike the monster.");
	}
}
