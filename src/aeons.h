#ifndef AEONS_H
#define AEONS_H
#include "config.h"
void set_aeon_state(int n);
void set_aeon_mood(int aeon_index, const char* new_mood);

void display_aeon_status();
void display_aeon_mood();
void receive_aeon_whispers();
int aeon_reacts_negatively();
int aeon_aligns_with_ritual(AeonProfile active_aeon, RitualType ritual_type);
int aeon_reacts_negatively(AeonProfile aeon, const char* glyph);
int aeon_reacts_positively(AeonProfile aeon, const char* glyph);
int get_aeon_mood_modifier();

#endif
