#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "externs.h"

#define PLAYER_CHAR '@'

#define LOG_MAX_LINES	10
#define LOG_LINE_LEN	80
#define LOG_BUFFER_SIZE	(LOG_MAX_LINES * LOG_LINE_LEN)

#define MSG_MORE	"(more)"
#define MSG_CUTOFF	"(trunc.)"

static char log[LOG_BUFFER_SIZE];
static int log_pos = 0;
static int log_line = 0;
static int log_total_lines = 0;

void clearInput()
{   
	//clears the input buffer 
	while (getchar() != '\n');
}

char select_difficulty()
{
	char temp;
	int notValid = 1;

	//Prompts user to pick a difficulty for the game
	while(notValid == 1)
	{
		temp = 0;
		printf("\n\n\nb - beginner, i - intermediate, a - advanced\n");
		printf("Please enter a difficulty ('b', 'i', or 'a'): ");

		//Reads in user input
		scanf("%c", &temp);

		//makes sure they enteres a valid value
		if(temp == 'b' || temp == 'B' || temp == 'i' || temp == 'I' || temp == 'a' || temp == 'A')
			notValid = 0;
		else
		{	
			printf("\nInvalid selection, please try again.");
			clearInput();
		}
	}
	printf("\n");
	clearInput();
	return temp;
}

void write_log(char* msg)
{
	int length = strlen(msg);

	// Ensure space for the message plus a ' '
	if (length + log_pos + 1 > LOG_BUFFER_SIZE)
		length = LOG_BUFFER_SIZE - log_pos - 1;

	// If we had enough room to write a space and at least some of the message
	if (length > 0) {
		// Message
		strncpy(&log[log_pos], msg, length);
		log_pos += length;

		// Trailing space
		log[log_pos] = ' ';
		log_pos++;

		// Update # of lines
		log_total_lines = 1 + (log_pos - 1) / LOG_LINE_LEN;
	}
}

void clear_log()
{
	log_pos = 0;
	log_line = 0;
	log_total_lines = 0;
}

void draw(level_t* level, player_t* player)
{
	erase();

	// Draw terrain, monsters, and the player
	int i, j;
	for (i = 0; i < level->width; ++i) {
		for (j = 0; j < level->height; ++j) {
			if (level->mon_map[i][j])
				mvwaddch(stdscr, level->height - j - 1, i, level->mon_map[i][j]->symbol | COLOR_PAIR(2));
			else
				mvwaddch(stdscr, level->height - j - 1, i, level->terrain[i][j]);
		}
	}
	mvwaddch(stdscr, level->height - player->y - 1, player->x, player->symbol | COLOR_PAIR(1));

	// Draw status info
	char status[LOG_LINE_LEN];
	snprintf(status, LOG_LINE_LEN, "HP: %d/%d", player->hp, player->max_hp);
	mvwaddstr(stdscr, level->height + 1, 0, status);

	// Draw log messages
	if (log_pos > 0) {
		int stop;

		if (log_line == log_total_lines - 1)
			stop = log_pos % LOG_LINE_LEN;
		else
			stop = LOG_LINE_LEN;

		for (int i = 0; i < stop; ++i)
			mvwaddch(stdscr, level->height, i, log[log_line * LOG_LINE_LEN + i]);
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
	char difficulty = select_difficulty();

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
	level.diff = difficulty;

	// Insert dummy monsters
	add_monster(&level, alloc_monster('M', 9, 9, 10));
	add_monster(&level, alloc_monster('M', 7, 9, 10));
	add_monster(&level, alloc_monster('M', 9, 7, 10));
	add_monster(&level, alloc_monster('M', 3, 5, 10));
	add_monster(&level, alloc_monster('M', 7, 2, 10));
	add_monster(&level, alloc_monster('M', 9, 11, 10));

	// Initialize player
	player_t player = init_player(PLAYER_CHAR, 1, 1, 20);

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
			if (input == ' ' && log_line < log_total_lines - 1)
				log_line++;
		
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

			if (player.hp <= 0)
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
