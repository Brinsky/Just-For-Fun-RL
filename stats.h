#ifndef STATS_H
#define STATS_H

typedef struct Stats
{
	int cur_hp;
	int max_hp;
	int attack;
	int defense;
	int accuracy;
	int evasion;
} Stats;

Stats init_stats(int, int, int, int, int, int);
int attack(Stats*, Stats*);

#endif
