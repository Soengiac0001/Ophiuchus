#ifndef RITUALS_H
#define RITUALS_H

void define_ritual(const char *name, const char *code, int aeon, int elemental);
void run_ritual(const char *name);
void save_rituals(const char *filename);
void load_rituals(const char *filename);
void perform_ritual(const char *ritual_name);
void invoke_symbolic_sequence();
void ritual_status();
void process_recent_rituals();
void perform_glyph_fusion(const char* glyphs[], int glyph_count);
void perform_aeon_combination(const char* aeons[], int aeon_count);
void execute_ritual_with(const char* glyph_name, const char* aeon_name);
void rcast_ritual(const char* ritual_name);
void run_ophiuchus_brain(void);
void display_visual_feedback(const char* context);
void handle_rcast();
void handle_aeon_combination();
void handle_glyph_fusion();
void handle_ritual_cast();
void invoke_mirror(void);
void apply_blessing();
void apply_curse();
void apply_neutral_effect();
void apply_chaotic_effect();
void random_blessing_or_curse();
void random_curse();
void random_blessing();
int calculate_ritual_energy();
#endif // RITUALS_H
