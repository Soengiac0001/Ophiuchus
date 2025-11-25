#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdint.h>
#include "config.h"

typedef struct {
    char name[STACK_NAME_LEN];
    int data[STACK_SIZE];
    int sp;
} NamedStack;

typedef enum {
    MODE_BASE,
    MODE_GLYPH,
} ModeType;

extern NamedStack stacks[MAX_STACKS];
extern int current_stack_index;
extern ModeType mode_stack[MODE_STACK_SIZE];
extern int mode_stack_top;
extern uint8_t memory[MEM_SIZE];
extern uint8_t stack[STACK_SIZE];
extern int pointer;
extern int sp;
extern int glyph_mode;
extern int trace_enabled;
extern FILE *trace_file;
extern int profile[256];
extern int frozen[MEM_SIZE];
extern int current_theme;

// Core control functions
ModeType pop_mode();
void run_ophiuchus_brain();
void view_sector(const char *sector);
void auto_snapshot_on_event(const char *event);
void poke_memory(int address, int value);
void peek_memory(int address);
void reset_interpreter();
void save_memory(const char *filename);
void load_memory(const char *filename);
void wrap_pointer();
void save_snapshot(const char *filename);
void load_snapshot(const char *filename);
void inspect_snapshot(const char *filename);
void export_environment(const char *filename);
void terminate();
void set_theme(const char *name);
void push_mode(ModeType mode);
void create_stack(const char *name);
void switch_stack(const char *name);
void push_stack(int value);
void list_stacks();
void cast_stack_spell(const char *spell);
void display_stack();
void show_pointer();
void run_tree();
void encrypt_sensitive_data();
void handle_theme_change();
void load_memory_prompt();
void save_memory_prompt();
void idle_brain_tick();
void track_user_behavior();
void ai_echo();
void adapt_environment();
void consult_oracle_if_needed();

int pop_stack();
int safe_stack_push(uint8_t value);
int safe_stack_pop(uint8_t *out);

#endif // CORE_H
