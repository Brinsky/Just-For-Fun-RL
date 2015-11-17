#ifndef LOG_H
#define LOG_H

#define LOG_LINE_LEN		80
#define LOG_MAX_LINES		10
#define LOG_BUFFER_SIZE 	(LOG_MAX_LINES * LOG_LINE_LEN)

void writef_log(char*, ...);
void write_log(char*);
void clear_log();
void log_next_line();
void log_prev_line();
int log_pos();
int log_line();
int log_total_lines();
char log_at(int);

#endif
