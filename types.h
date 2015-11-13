/* Global type declarations */

#ifndef TYPES_H
#define TYPES_H

#define LOG_LINE_LEN		80
#define LOG_MAX_LINES		10
#define LOG_BUFFER_SIZE 	(LOG_MAX_LINES * LOG_LINE_LEN)

typedef struct stats_t
{
	int cur_hp;
	int max_hp;
	int attack;
	int defense;
	int accuracy;
	int evasion;
} stats_t;

typedef struct player_t
{
	char symbol;
	stats_t stats;
	int x;
	int y;
} player_t;

typedef struct monster_t
{
	char symbol;
	stats_t stats;
	int x;
	int y;
	// Used to build linked list of all monsters in a level
	struct monster_t* next;
	struct monster_t* prev;
} monster_t;

typedef struct log_t
{
	int pos; // Last character position 
	int line; // Line currently being viewed
	int length; // Total # of lines
	char buffer[LOG_BUFFER_SIZE];
} log_t;

typedef struct level_t
{
	int width;
	int height;
	char** terrain; // 2D array of chars
	monster_t*** mon_map; // 2D array of monster_t*
	monster_t* mon_list; // List of all living monsters
} level_t;

#endif
