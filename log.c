#include <string.h>

#include "types.h"
#include "externs.h"

log_t turn_log;

void init_log()
{
	clear_log(turn_log);
}

void write_log(char* msg)
{
	int length = strlen(msg);

	// Ensure space for the message plus a ' '
	if (length + turn_log.pos + 1 > LOG_BUFFER_SIZE)
		length = LOG_BUFFER_SIZE - turn_log.pos - 1;

	// If we had enough room to write a space and at least some of the message
	if (length > 0) {
		// Message
		strncpy(&turn_log.buffer[turn_log.pos], msg, length);
		turn_log.pos += length;

		// Trailing space
		turn_log.buffer[turn_log.pos] = ' ';
		turn_log.pos++;

		// Update # of lines
		turn_log.length = 1 + (turn_log.pos - 1) / LOG_LINE_LEN;
	}
}

void clear_log()
{
	turn_log.pos = 0;
	turn_log.line = 0;
	turn_log.length = 0;
}
