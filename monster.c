#include <stdio.h>
#include <stdlib.h>

#include "externs.h"
#include "types.h"

monster_t* alloc_monster(char symbol, int x, int y, int hp)
{
	monster_t* monster = malloc(sizeof(monster_t));
	monster->symbol = symbol;
	monster->x = x;
	monster->y = y;
	monster->stats = init_stats(hp, hp, 10, 10, 10, 10);

	monster->next = NULL;
	monster->prev = NULL;

	return monster;
}

/* Process a monster's turn */
void monster_turn(monster_t* monster, level_t* level, player_t* player)
{
	int distX = monster->x - player->x;
	int distY = monster->y - player->y;

	// Attack the player if close enough
	if (distX >= -1 && distX <= 1 && distY >= -1 && distY <= 1) {
		int dmg = attack(&player->stats, &monster->stats);
		if (dmg >= 0)
			writef_log("Monster hits you for %d damage.", dmg);
		else
			write_log("Monster misses you.");
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

		// Move towards the player if possible
		if (is_open(level, monster->x + x, monster->y + y)) {
			level->mon_map[monster->x][monster->y] = NULL;
			monster->x += x;
			monster->y += y;
			level->mon_map[monster->x][monster->y] = monster;
		}
	}
}

/* Process a player v. monster attack */
void hit_monster(monster_t* monster, level_t* level, player_t* player)
{
	int dmg = attack(&monster->stats, &player->stats);

	if (dmg > 0)
		writef_log("You hit monster for %d damage.", dmg);
	else
		write_log("You miss the monster.");

	if (monster->stats.cur_hp <= 0) {
		rm_monster(level, monster);
		write_log("You kill the monster.");
	}

	writef_log("(Monster HP: %d)", monster->stats.cur_hp);
}
