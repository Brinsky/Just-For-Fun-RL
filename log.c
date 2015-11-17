#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "log.h"

static int pos = 0; // Next open character position
static int line = 0; // Line currently being viewed
static int total_lines = 0; // Total # of lines
static char buffer[LOG_BUFFER_SIZE];

void writef_log(char* format, ...)
{
	// Deal with variable argument list
	va_list ap;
	va_start(ap, format);

	// Write out as much as we have room for (or just the whole message)
	int remaining_space = LOG_BUFFER_SIZE - pos;
	pos += vsnprintf(&buffer[pos],
			remaining_space, format, ap);

	// Insert trailing space
	if (pos < LOG_BUFFER_SIZE) {
		buffer[pos] = ' ';
		pos++;
	}

	// Update # of lines
	total_lines = 1 + (pos - 1) / LOG_LINE_LEN;
	
	// Cleanup
	va_end(ap);
}

void write_log(char* msg)
{
	writef_log(msg);
}

void clear_log()
{
	pos = 0;
	line = 0;
	total_lines = 0;
}

void log_next_line()
{
	if (line < total_lines - 1)
		line++;
}

void log_prev_line()
{
	if (line > 0)
		line--;
}

int log_pos()
{
	return pos;
}

int log_line()
{
	return line;
}

int log_total_lines()
{
	return total_lines;
}

char log_at(int index)
{
	return buffer[index];
}
