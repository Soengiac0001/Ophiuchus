#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config.h"
#include "utils.h"
#include "aeons.h"
#include "core.h"
#include "glyphs.h"
#include "brain.h"
#include "rituals.h"
#include "elemental_synergy.h"

// ===== utilities for Ophiuchus =====

extern int debug_mode;
extern char dream_log[][256];

// ====== To Be Updated ======
void clear_memory_sector(const char* message) {
    (void)message;  // placeholder: will use this later
    printf("Update \n");
}

void corrupt_stack(const char* message) {
    (void)message;
    printf("Update \n");
}

void stabilize_memory(const char* message) {
    (void)message;
    printf("Update \n");
}

void invert_pointer(const char* message) {
    (void)message;
    printf("Update \n");
}

void secure_memory_sector(const char* message) {
    (void)message;
    printf("Update \n");
}

void unlock_random_ritual(const char* message) {
    (void)message;
    printf("Update \n");
}

void confuse_glyphs(const char* message) {
    (void)message;
    printf("Update \n");
}

void randomize_modes(const char* message) {
    (void)message;
    printf("Update \n");
}

void freeze_ritual_energy(const char* message) {
    (void)message;
    printf("Update \n");
}

void spike_stack(const char* message) {
    (void)message;
    printf("Update \n");
}

void shuffle_memory(const char* message) {
    (void)message;
    printf("Update \n");
}

void blur_dream(const char* message) {
    (void)message;
    printf("Update \n");
}

void reset_elemental_flux(const char* message) {
    (void)message;
    printf("Update \n");
}

// ====== Updated & functioning =======
void set_color(int color_code) {
    printf("\033[38;5;%dm", color_code);
}

static SpiralLock locks[] = {
    {"hidden_sector", "VeilRite", "Mist", "Kaelar"},
    {"chaos_node",    "StormBind", "Storm", "Xel'ara"},
    {"light_archive", "LuminSeal", "Light", "Thalen"}
};

void dump_state() {
    printf("🌀 System State:\n");
    printf("- Pointer:        %d\n", pointer);
    printf("- Memory Value:   %d\n", memory[pointer]);
    printf("- Stack Pointer:  %d\n", sp);
    printf("- Aeon State:     %d\n", aeon_state);
    printf("- Glyph Mode:     %s\n", glyph_mode ? "ON" : "OFF");
    
    if (current_theme == 2) {
        printf("🌀 System State:\n");
        printf("📍 Pointer:        %d\n", pointer);
        printf("🔢 Value:          %d\n", memory[pointer]);
        printf("🧠 Stack Pointer:  %d\n", sp);
        printf("✨ Aeon State:     %d\n", aeon_state);
        printf("🧿 Glyph Mode:     %s\n", glyph_mode ? "ON" : "OFF");
    } else {
        printf("Pointer: %d\n", pointer);
        printf("Value: %d\n", memory[pointer]);
        printf("Stack Pointer: %d\n", sp);
        printf("Aeon State: %d\n", aeon_state);
    }
    
    if (debug_mode) {
        printf("🔍 [DEBUG] Recent Dream Reflection: \"%s\"\n", dream_log[(dream_log_index - 1 + DREAM_LOG_SIZE) % DREAM_LOG_SIZE]);
        printf("🔍 [DEBUG] Last Opcode Profiled: ");
        for (int i = 0; i < 256; i++) {
            if (profile[i] > 0) {
                printf("%c ", i);
            }
        }
        printf("\n");
    }
}

// ======= Guides and Help =======

// ======= Major Functions from Utilities =======

void check_spiral_lock(const char* lock_name) {
    for (size_t i = 0; i < sizeof(locks)/sizeof(locks[0]); i++) {
        if (strcmp(lock_name, locks[i].lock_name) == 0) {

            if (!ritual_performed(locks[i].required_ritual)) {
                ai_echo_custom("Spiral Lock", "📜 A forgotten ritual seals this path...");
                printf("Hint: Perform the '%s' ritual.\n", locks[i].required_ritual);
                return;
            }

            if (!element_recently_invoked(locks[i].required_element)) {
                ai_echo_custom("Spiral Lock", "✨ The elemental flow is misaligned...");
                printf("Hint: Invoke synergy with %s.\n", locks[i].required_element);
                return;
            }

            if (strcmp(active_aeon.name, locks[i].required_aeon) != 0) {
                ai_echo_custom("Spiral Lock", "🌙 The wrong Aeon stands guard...");
                printf("Hint: Align with Aeon %s.\n", locks[i].required_aeon);
                return;
            }

            printf("✅ Spiral Lock '%s' opens. Access granted.\n", lock_name);
            return;
        }
    }

    printf("⚠️ Unknown Spiral Lock: %s\n", lock_name);
}

void run_step(const char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '0') { run_instruction('0'); continue; }
        if (glyph_mode) {
            char buf[5] = {0};
            int len = mblen(&line[i], MB_CUR_MAX);
            if (len < 1 || len > 4) continue;

            strncpy(buf, &line[i], (size_t)len);  // explicit, safe after the check
            i += len - 1;

            run_instruction(line[i]);
        }
    }
}

int ritual_performed(const char* ritual_name) {
    (void)ritual_name;  // placeholder
    // TODO: Implement real tracking
    return 1;  // Assume true for now
}

int element_recently_invoked(const char* element) {
    (void)element;  // placeholder
    // TODO: Implement real tracking
    return 1;  // Assume true for now
}

void display_spiral_pattern(const char* context, const char* element, int intensity) {
    srand((unsigned)time(NULL));
    int chance = rand() % 100;

    // 🌟 1% Chance for Perfect Spiral
    if (chance == 0) {
        set_color(201);  // Magical Pink
        printf("✨ A Perfect Spiral manifests! ✨\n");
        printf("     @@@\n");
        printf("   @     @\n");
        printf("  @       @\n");
        printf("   @     @\n");
        printf("     @@@\n" COLOR_RESET);
        return;
    }

    // Element ➜ Color Mapping
    if (strcmp(element, "Fire") == 0) set_color(196);
    else if (strcmp(element, "Water") == 0) set_color(39);
    else if (strcmp(element, "Storm") == 0) set_color(27);
    else if (strcmp(element, "Mist") == 0) set_color(250);
    else if (strcmp(element, "Light") == 0) set_color(226);
    else if (strcmp(element, "Shadow") == 0) set_color(90);
    else if (strcmp(element, "Earth") == 0) set_color(94);
    else if (strcmp(element, "Void") == 0) set_color(16);
    else if (strcmp(element, "Aether") == 0) set_color(201);
    else if (strcmp(element, "Ice") == 0) set_color(123);
    else if (strcmp(element, "Lightning") == 0) set_color(51);
    else if (strcmp(element, "Origin") == 0) set_color(220);
    else set_color(15);  // Default White

    // 🌪️ Contextual Patterns
    if (strcmp(context, "ritual") == 0) {
        printf("🌀 Ritual Energy Pattern (Level %d):\n", intensity);
        for (int i = 0; i < intensity; i++) {
            printf("   ~ ~ ~ ~\n");
        }
    }
    else if (strcmp(context, "glyph") == 0) {
        printf("🔹 Glyph Resonance (Level %d):\n", intensity);
        for (int i = 0; i < intensity; i++) {
            printf("   *   *\n");
            printf("    * *\n");
        }
    }
    else if (strcmp(context, "synergy") == 0) {
        printf("⚡ Elemental Convergence (Power %d):\n", intensity);
        for (int i = 0; i < intensity; i++) {
            printf("   /\\  /\\\n");
        }
    }
    else if (strcmp(context, "mirror") == 0) {
        printf("🪞 Reflection Distortion:\n");
        for (int i = 0; i < intensity; i++) {
            printf("   <>  <>\n");
        }
    }
    else {
        printf("🌌 The Spiral shimmers mysteriously...\n");
    }

    printf(COLOR_RESET);
}
