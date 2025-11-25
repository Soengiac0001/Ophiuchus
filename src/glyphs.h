#ifndef GLYPHS_H
#define GLYPHS_H



void create_glyph_memory(const char* aeon_name, int use_origin);
void define_custom_glyph(const char *name, const char *sequence, const char *element, const char *effect);
void list_custom_glyphs();
void print_aeon_glyphs();
void display_glyphs();
void run_instruction(char instr);
void translate_glyph(const char* glyph);
void translate_opcode(char opcode);
void interact_with_glyphs();
void save_user_glyph(const char* glyph_name, const char* element, const char* aeon_holder, const char* planet);
void handle_glyph_creation();
int glyph_to_opcode(const char *glyph);
int glyph_to_opcode(const char *glyph);


#endif // GLYPHS_H

