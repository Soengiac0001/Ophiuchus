#include <stdint.h>

#ifndef CONFIG_H
#define CONFIG_H

// === DEFINE ===
#define ORIGIN_PHRASE "🜏 Do not underestimate the power of Origin."
#define DREAM_LOG_SIZE 10
#define MAX_USER_RITUALS 32
#define DREAM_LOG_SIZE 10
#define DREAM_BUFFER_SIZE 512
#define debug_log(msg) if (debug_mode) { printf("🐞 DEBUG: %s\n", msg); }
#define MAX_RITUALS 64
#define RITUAL_NAME_LEN 32
#define RITUAL_CODE_LEN 256
#define MEM_SIZE 65536
#define STACK_SIZE 1028
#define LINE_MAX 512
#define BASE_PATTERN_COUNT 60
#define SECTOR_CORE_GLYPHS_START    0
#define SECTOR_RITUAL_SPACE_START   1024
#define SECTOR_DREAM_BUFFER_START   2048
#define SECTOR_ORACLE_LOGS_START    3072
#define SECTOR_ELEMENTAL_FLUX_START 4096
#define SECTOR_FREE_MEMORY_START    5120
#define MODE_STACK_SIZE 10
#define MAX_STACKS 8
#define MAX_CUSTOM_GLYPHS 64
#define STACK_NAME_LEN 16
#define COLOR_RESET "\033[0m"

// === ENUMS ===
typedef enum { POS, NEG, NEU} PolarityType;
typedef enum { POSITIVE, NEGATIVE, NEUTRAL} GlyphPolarity;
typedef enum { RITUAL_HARMONY, RITUAL_POWER, RITUAL_TRANSFORMATION, RITUAL_PROTECTION, RITUAL_DIVINATION, RITUAL_CHAOS } RitualType;

// === GLOBAL STRUCTS ===
typedef struct {
    char *name;
    char *effect;
    int mood;
} Elemental;

typedef struct {
    char name[20];
    char abbrev[5];
    char element[12];
    char planet[16];
    int base_influence;
    int polarity;
    char mood[15];
} AeonProfile;

typedef struct {
    const char* combo_key;
    const char* result;
} SynergyPattern;

typedef struct {
    char name[32];
    char element[16];
    char aeon_holder[16];
    char planet[16];
} CustomGlyph;

typedef struct {
    char name[RITUAL_NAME_LEN];
    char code[RITUAL_CODE_LEN];
    int required_aeon;     // 0 = any
    int requires_elemental;  // 1 = needs elemental mode
} Ritual;

typedef struct {
    char name[32];
    char glyphs[5][32];  // Up to 5 glyph names per ritual
    int glyph_count;
    char outcome[64];  // The system's symbolic result
    char effect_code[32];   // e.g., "RESET_PTR" or "MIRROR_SHIFT"
    char allowed_time[32];  // e.g., "FRIDAY", "FULLMOON", "13:00-14:00"
} UserRitual;

typedef struct {
    char name[32];
    RitualType type;
    char glyph_used[16];
} ActiveRitual;

typedef struct {
    const char* lock_name;
    const char* required_ritual;
    const char* required_element;
    const char* required_aeon;
} SpiralLock;

// === GLOBALS ===
extern FILE *trace_file;
extern const char* get_aeon_polarity(const char* aeon_name);

extern int glyph_level;
extern int glyph_count;
extern int glyph_counter;
extern int glyph_mode;

extern int spiral_stress;

extern int positive_rituals;
extern int negative_rituals;
extern int ritual_count;
extern int ritual_energy;
extern int ritual_energy_max;
extern int sp;
extern int trace_enabled;
extern void influence_brain_soul(const char* element);
extern void append_to_dream(const char* message);
extern void adjust_aeon_emotion(const char* message);
extern int pointer;
extern int brain_focus_level;
extern int brain_stability;
extern int dream_log_index;
extern int chaos_triggers;
extern int mirror_invokes;
extern int storm_usage;
extern int water_usage;
extern int current_mood;
extern int inactivity_counter;
extern int total_visuals_triggered;
extern int encryption_level;
extern void check_hidden_dream_prophecy();
extern char last_thought[128];
extern char element_core_lowercase[32];
extern const char* element_names[];

// === SHARED ARRAYS ===
extern uint8_t memory[MEM_SIZE];
extern uint8_t stack[STACK_SIZE];

extern SynergyPattern base_patterns[BASE_PATTERN_COUNT];
extern UserRitual user_rituals[MAX_USER_RITUALS];
extern Elemental elementals[13];
extern CustomGlyph custom_glyphs[MAX_CUSTOM_GLYPHS];
extern Ritual rituals[MAX_RITUALS];
extern AeonProfile aeons[13];
extern AeonProfile active_aeon;
extern GlyphPolarity get_glyph_polarity(const char* glyphs);
extern int aeon_state;
extern const char* aeon_moods[];
extern char glyph_name[64];
extern char hidden_dream_buffer[256];
void ai_echo(const char* context);
extern char dream_log[DREAM_LOG_SIZE][256];
extern char dream_buffer[512];
extern int frozen[];
extern int dream_index;
extern int debug_mode;
extern char glyph_used[64];
extern int ritual_type;
extern int fusion_count;
extern int aeon_combo_count;
extern int ritual_cast_count;
extern char active_element[32];
extern int ritual_level;
extern void append_to_dream(const char* message);
extern char last_ritual[64];
extern char dynamic_result[128];
extern int spiral_stress;
extern int current_mood;
extern int aeon_aligns_with_ritual(AeonProfile active_aeon, RitualType ritual_type);
extern int aeon_reacts_negatively(AeonProfile aeon, const char* glyph);
extern int aeon_reacts_positively(AeonProfile aeon, const char* glyph);

void save_brain_state();
void run_brain_echo(const char* event_type, const char* detail);
void update_aeon_mood(const char *trigger);
void guide_glyphs();
void guide_rituals();
void guide_aeons();
void guide_mirror();
void guide_dream();
void guide_about();
void list_rituals();
void list_user_rituals();
void corrupt_stack();

#endif
