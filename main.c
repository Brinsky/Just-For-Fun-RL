#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "externs.h"

#define PLAYER_CHAR '@'

void draw(level_t* level, player_t* player)
{
	erase();

	// Draw terrain, monsters, and the player
	int i, j;
	for (i = 0; i < level->width; ++i) {
		for (j = 0; j < level->height; ++j) {
			if (level->mon_map[i][j])
				mvwaddch(stdscr, level->height - j - 1, i,
						level->mon_map[i][j]->symbol | COLOR_PAIR(2));
			else
				mvwaddch(stdscr, level->height - j - 1,
						i, level->terrain[i][j]);
		}
	}
	mvwaddch(stdscr, level->height - player->y - 1,
			player->x, player->symbol | COLOR_PAIR(1));

	// Draw status info
	char status[LOG_LINE_LEN];
	snprintf(status, LOG_LINE_LEN, "HP: %d/%d", player->stats.cur_hp, player->stats.max_hp);
	mvwaddstr(stdscr, level->height + 1, 0, status);

	// Draw log messages
	if (turn_log.pos > 0) {
		int stop;

		if (turn_log.line == turn_log.length - 1)
			stop = turn_log.pos % LOG_LINE_LEN;
		else
			stop = LOG_LINE_LEN;

		for (int i = 0; i < stop; ++i)
			mvwaddch(stdscr, level->height, i,
					turn_log.buffer[turn_log.line * LOG_LINE_LEN + i]);
	}

	refresh();
}

/* Process each monster's turn */
void monster_turns(level_t* level, player_t* player)
{
	monster_t* current = level->mon_list;
	while (current) {
		monster_turn(current, level, player);

		// Cycle to next monster
		current = current->next;
	}
}

int main()
{
	srand(time(NULL));

	// ncurses setup
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	start_color();
	curs_set(FALSE);

	// Color setup
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

	// Initialize level
	level_t level = init_level(15, 15);

	// Insert dummy monsters
	add_monster(&level, alloc_monster('M', 9, 9, 10));
	add_monster(&level, alloc_monster('M', 7, 9, 10));
	add_monster(&level, alloc_monster('M', 9, 7, 10));
	add_monster(&level, alloc_monster('M', 3, 5, 10));
	//add_monster(&level, alloc_monster('M', 7, 2, 10));
	//add_monster(&level, alloc_monster('M', 9, 11, 10));

	// Initialize player
	player_t player = init_player(PLAYER_CHAR, 1, 1, 20);

	// Initialize log
	init_log();

	bool running = TRUE;
	bool dead = FALSE;
	int input = 0;
	draw(&level, &player);
	
	while (running && !dead) {
		// Input loop, exit on pressing 'q' or 'Q'
		while ((input = getch()) != ERR) {
			// Exit the game
			if (input == 'q' || input == 'Q')
				running = FALSE;

			// Cycle through log lines
			if (input == ' ' && turn_log.line < turn_log.length - 1)
				turn_log.line++;
		
			// Movement/action inputs
			int x = 0, y = 0;	
			if (input == KEY_LEFT || input == '4') {
				x = -1;
			} else if (input == KEY_HOME || input == '7') {
				x = -1;
				y = 1;
			} else if (input == KEY_UP || input == '8') {
				y = 1;
			} else if (input == KEY_PPAGE || input == '9') {
				x = 1;
				y = 1;
			} else if (input == KEY_RIGHT || input == '6') {
				x = 1;
			} else if (input == KEY_NPAGE || input == '3') {
				x = 1;
				y = -1;
			} else if (input == KEY_DOWN || input == '2') {
				y = -1;
			} else if (input == KEY_END || input == '1') {
				x = -1;
				y = -1;
			}

			// Temporary hack to determine if anything was done
			if (x != 0 || y != 0 || input == '5') {
				clear_log();
				attempt_act(&level, &player, x, y);
				monster_turns(&level, &player);
			}

			draw(&level, &player);

			if (player.stats.cur_hp <= 0)
				dead = TRUE;
		}
	}

	if (dead) {
		erase();
		mvwaddstr(stdscr, 0, 0, "You died. Press space to quit.");
		refresh();
		while (getch() != ' ');
	}

	// Cleanup
	endwin();
	cleanup_level(&level);

	return 0;
}
