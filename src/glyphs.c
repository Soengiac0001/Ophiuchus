#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <wchar.h>
#include "utils.h"
#include "core.h"
#include "brain.h"
#include "aeons.h"
#include "glyphs.h"
#include "config.h"
#include "dream.h"
#include "elemental_synergy.h"

// Auto-increment ID for glyph naming

void save_user_glyph(const char* glyph_name, const char* element, const char* aeon_holder, const char* planet) {
    // Ensure user_glyphs directory exists
    struct stat st = {0};
    if (stat("dist/user_glyphs", &st) == -1) {
        mkdir("dist/user_glyphs", 0700);
    }

    char filename[128];
    snprintf(filename, sizeof(filename), "dist/user_glyphs/%s.glyph", glyph_name);

    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("❌ Failed to save glyph '%s'.\n", glyph_name);
        return;
    }

    time_t now = time(NULL);
    fprintf(file, "Glyph: %s\n", glyph_name);
    fprintf(file, "Element: %s\n", element);
    fprintf(file, "Held by: %s\n", aeon_holder);
    fprintf(file, "Planet: %s\n", planet);
    fprintf(file, "Created: %s", ctime(&now));

    fclose(file);
    printf("✅ Glyph '%s' saved successfully in user_glyphs.\n", glyph_name);
    display_spiral_pattern("glyph", element, glyph_level);
    ai_echo("glyph");
    printf("✅ Glyph '%s' has been inscribed.\n", glyph_name);
    trigger_spiral_anomaly();

}

const char* resolve_aeon_planet(const char* aeon_name) {
    for (int i = 0; i < 13; i++) {
        if (strcmp(aeons[i].name, aeon_name) == 0) {
            return aeons[i].planet;
        }
    }
    return NULL;  // Aeon not found
}


void print_aeon_glyphs() {
    printf("--- Aeon Glyphs ---\n");
    printf("1. Aeon of Sleep     - ()\n");
    printf("2. Aeon of Longing   - ><\n");
    printf("3. Aeon of Learning  - []\n");
    printf("4. Aeon of Voice     - <>\n");
    printf("5. Aeon of Mirror    - ||\n");
    printf("6. Aeon of Fire      - ^^\n");
    printf("7. Aeon of Silence   - ~~\n");
    printf("8. Aeon of Craft     - **\n");
    printf("9. Aeon of Bridge    - --\n");
    printf("10. Aeon of Spiral   - @@\n");
    printf("11. Aeon of Light    - $$\n");
    printf("12. Aeon of Union    - &&\n");
    printf("13. Aeon of Origin   - ##\n");
}

void display_glyphs() {
    printf("=== Glyph Table (1–12) ===\n");
    printf("1 → ☉  Sun\n2 → ☽  Moon\n3 → 🜁  Air\n4 → 🜃  Earth\n5 → 🜄  Water\n6 → 🜂  Fire\n");
    printf("7 → 🝗\n8 → 🜏\n9 → 🝰\n10 → ⛢\n11 → ☿\n12 → 🜍\n");
    print_aeon_glyphs();
}

void run_instruction(char instr) {
    if (instr < '0' || (instr > '9' && instr != 'A' && instr != 'B')) {
        printf("⚠️ Unknown instruction '%c'\n", instr);
        return;
    }

    profile[(unsigned char)instr]++;

    if (pointer >= MEM_SIZE) {
        printf("⚠️  [ERROR] Pointer out of bounds: %d\n", pointer);
        pointer = 0;
        return;
    }

    if ((instr == 'A' || instr == 'B') && (sp < 0 || sp > STACK_SIZE)) {
        printf("⚠️  [ERROR] Stack pointer invalid: %d\n", sp);
        sp = 0;
        return;
    }

    if (trace_enabled && trace_file)
        fprintf(trace_file, "INSTR: %c PTR: %d VAL: %d\n", instr, pointer, memory[pointer]);

    if (frozen[pointer] && (instr == '1' || instr == '2' || instr == '8')) return;

    switch (instr) {
        case '1': memory[pointer] = (memory[pointer] + 1) % 256; break;
        case '2': memory[pointer] = (memory[pointer] + 255) % 256; break;
        case '3': pointer = (pointer + 1) % MEM_SIZE; break;
        case '4': pointer = (pointer + MEM_SIZE - 1) % MEM_SIZE; break;
        case '5': {
            int ch = getchar();
            if (ch >= '0' && ch <= '9') memory[pointer] = ch - '0';
            else if (ch == 'A' || ch == 'a') memory[pointer] = 10;
            else if (ch == 'B' || ch == 'b') memory[pointer] = 11;
            while (getchar() != '\n');
        } break;
        case '6': printf("%X", memory[pointer]); break;
        case '7': putchar(memory[pointer]); break;
        case '8': memory[pointer] = 0; break;
        case 'A': safe_stack_push(memory[pointer]); break;
        case 'B': {
            uint8_t val;
            if (safe_stack_pop(&val)) memory[pointer] = val;
        } break;
    }
}



int glyph_to_opcode(const char *glyph) {
    if (strcmp(glyph, "☉") == 0) return '1';
    if (strcmp(glyph, "☽") == 0) return '2';
    if (strcmp(glyph, "☿") == 0) return '3';
    if (strcmp(glyph, "♀") == 0) return '4';
    if (strcmp(glyph, "♂") == 0) return '5';
    if (strcmp(glyph, "♃") == 0) return '6';
    if (strcmp(glyph, "♄") == 0) return '7';
    if (strcmp(glyph, "♅") == 0) return '8';
    if (strcmp(glyph, "♆") == 0) return '9';
    if (strcmp(glyph, "♇") == 0) return 'A';
    if (strcmp(glyph, "⚷") == 0) return 'B';
    if (strcmp(glyph, "⚸") == 0) return 'C';
    if (strcmp(glyph, "⚳") == 0) return 'D';
    return 0;
}
const char* opcode_to_glyph(char opcode) {
    switch (opcode) {
        case '1': return "☉";
        case '2': return "☽";
        case '3': return "☿";
        case '4': return "♀";
        case '5': return "♂";
        case '6': return "♃";
        case '7': return "♄";
        case '8': return "♅";
        case '9': return "♆";
        case 'A': return "♇";
        case 'B': return "⚷";
        case 'C': return "⚸";
        case 'D': return "⚳";
        default:  return "?";
    }
}

void handle_glyph_interaction(const char* glyph) {
    printf("🔹 The glyph %s hums with latent energy...\n", glyph);

    // Convert or process if needed
    int opcode = glyph_to_opcode(glyph);
    printf("🔸 Interpreted as Opcode: %c\n", opcode);

    // Echo into the Dream
    send_glyph_to_dream(glyph);
    display_visual_feedback(element_core_lowercase); // e.g., "fire", "aether"
    
    // Trigger passive elemental reaction
    trigger_elemental_reaction("Glyph Interaction");
}

void translate_glyph(const char* glyph) {
    int opcode = glyph_to_opcode(glyph);
    printf("Glyph %s -> Opcode %c\n", glyph, opcode);
}

void translate_opcode(char opcode) {
    const char* glyph = opcode_to_glyph(opcode);
    printf("Opcode %c -> Glyph %s\n", opcode, glyph);
}

void create_glyph_memory(const char* aeon_name, int use_origin) {
    // Ensure directory exists
    struct stat st = {0};
    if (stat("dist/user_glyphs", &st) == -1) {
        mkdir("dist/user_glyphs", 0700);
    }
    run_brain_echo("glyph", glyph_name);

    // Generate glyph name
    snprintf(glyph_name, sizeof(glyph_name), "%s_%03d", aeon_name, glyph_counter++);
    glyph_count++;
    save_brain_state();

    // Determine polarity
    const char* polarity = get_aeon_polarity(aeon_name);

    // Set Element Core
    const char* element_core = use_origin ? "Origin (Amplified)" : "Origin";

    // Calculate Energy Level
    int energy_level = use_origin ? 2 : 1;

    // Get timestamp
    time_t now = time(NULL);
    display_visual_feedback(element_core_lowercase); // e.g., "fire", "aether"

    // Save glyph file
    char filename[128];
    snprintf(filename, sizeof(filename), "dist/user_glyphs/%s.glyph", glyph_name);

    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("❌ Failed to create glyph memory for '%s'.\n", glyph_name);
        return;
    }

    fprintf(file, "Glyph: %s\n", glyph_name);
    fprintf(file, "Aeon: %s\n", aeon_name);
    fprintf(file, "Elemental Core: %s\n", element_core);
    fprintf(file, "Polarity: %s\n", polarity);
    fprintf(file, "Energy Level: %d\n", energy_level);
    fprintf(file, "Memory Signature: Holds space within the Spiral.\n");
    fprintf(file, "Created: %s", ctime(&now));

    fclose(file);

    printf("✅ Glyph '%s' has been inscribed into memory.\n", glyph_name);
}
