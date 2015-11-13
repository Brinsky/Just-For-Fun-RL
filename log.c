#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "types.h"
#include "externs.h"

log_t turn_log;

void init_log()
{
	clear_log(turn_log);
}

void writef_log(char* format, ...)
{
	// Deal with variable argument list
	va_list ap;
	va_start(ap, format);

	// Write out as much as we have room for (or just the whole message)
	int remaining_space = LOG_BUFFER_SIZE - turn_log.pos;
	turn_log.pos += vsnprintf(&turn_log.buffer[turn_log.pos],
			remaining_space, format, ap);

	// Insert trailing space
	if (turn_log.pos < LOG_BUFFER_SIZE) {
		turn_log.buffer[turn_log.pos] = ' ';
		turn_log.pos++;
	}

	// Update # of lines
	turn_log.length = 1 + (turn_log.pos - 1) / LOG_LINE_LEN;
	
	// Cleanup
	va_end(ap);
}

void write_log(char* msg)
{
	writef_log(msg);
}

void clear_log()
{
	turn_log.pos = 0;
	turn_log.line = 0;
	turn_log.length = 0;
}
