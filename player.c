#include <stdio.h>

#include "types.h"
#include "externs.h"

player_t init_player(char symbol, int x, int y, int max_hp)
{
	player_t player;

	player.symbol = symbol;
	player.x = x;
	player.y = y;
	player.stats = init_stats(max_hp, max_hp, 12, 12, 12, 12);

	return player;
}

/* Attempt to attack or move in a given direction, depending on context */
void attempt_act(level_t* level, player_t* player, int deltaX, int deltaY)
{
	int newX = player->x + deltaX;
	int newY = player->y + deltaY;

	if (newX < 0 || newX >= level->width || newY < 0 || newY >= level->height)
		return;

	if (level->mon_map[newX][newY]) {
		hit_monster(level->mon_map[newX][newY], level, player);
	} else if (level->terrain[newX][newY] == '.') {
		player->x = newX;
		player->y = newY;
	}
}
