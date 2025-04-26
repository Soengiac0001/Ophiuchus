#ifndef DREAM_H
#define DREAM_H

void enter_dream_mode();
void show_dream_vision();
void process_dream_command(const char *input);
void reflect_in_dream(const char* event);
void init_dream();
void init_dream_buffer();
void flush_dream_buffer();
void dream_log_state();
void show_dream_log();
void save_dream_state(const char* filename);
void load_dream_state(const char* filename);
void send_glyph_to_dream(const char* glyph);
void reset_dream_flux();          // dream.h


#endif //dream_h


