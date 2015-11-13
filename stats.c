#include <stdlib.h>

#include "types.h"

stats_t init_stats(int cur_hp, int max_hp, int attack, int defense, int accuracy, int evasion)
{
	stats_t stats;

	stats.cur_hp = cur_hp;
	stats.max_hp = max_hp;
	stats.attack = attack;
	stats.defense = defense;
	stats.accuracy = accuracy;
	stats.evasion = evasion;
	
	return stats;
}

/* Inclusive */
int rand_between(int low, int high)
{
	return low + (rand() % (high - low - 1));
}

/* Returns amount of damage dealt. Value is negative for missed attacks */
int attack(stats_t* defender, stats_t* attacker)
{
	int eva_roll = defender->evasion + rand_between(-4, 1);
	int acc_roll = attacker->accuracy + rand_between(-1, 6);

	if (eva_roll > acc_roll)
		return -1;

	int def_roll = defender->defense / 2 + rand_between(-2, 1);
	int att_roll = attacker->attack / 2 + rand_between(-1, 2);

	int dmg = (att_roll > def_roll) ? (att_roll - def_roll) : 0;
	defender->cur_hp -= dmg;

	return dmg;
}
