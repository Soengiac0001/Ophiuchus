#ifndef UTILS_H
#define UTILS_H

void print_help();
void dump_state();
void wait_for_enter();
void clear_screen();
void check_spiral_lock(const char* lock_name);
void run_step(const char *line);
int ritual_performed(const char* ritual_name);
int element_recently_invoked(const char* element);
void display_spiral_pattern(const char* context, const char* element, int intensity);

#endif // UTILS_H
