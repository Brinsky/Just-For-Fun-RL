#ifndef STATS_H
#define STATS_H

typedef struct stats_t
{
	int cur_hp;
	int max_hp;
	int attack;
	int defense;
	int accuracy;
	int evasion;
} stats_t;

stats_t init_stats(int, int, int, int, int, int);
int attack(stats_t*, stats_t*);

#endif
