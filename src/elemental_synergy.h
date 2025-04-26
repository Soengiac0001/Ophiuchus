#ifndef ELEMENTAL_SYNERGY_H
#define ELEMENTAL_SYNERGY_H

void check_elemental_reactions();
void influence_by_aeon(int aeon_state);
void shift_personality_with_elements();
void load_elemental_defaults();
void handle_elemental_distortion();
void clear_recent_synergies();    // elemental_synergy.h
void trigger_elemental_reaction(const char* context);
const char* generate_synergy_result(const char* elements[], int count, int glyph_level);
int get_element_polarity(const char* element);

#endif
