#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "core.h"
#include "glyphs.h"

NamedStack stacks[MAX_STACKS];
ModeType mode_stack[MODE_STACK_SIZE];

void save_memory(const char *filename);
void load_memory(const char *filename);


void push_mode(ModeType mode) {
    if (mode_stack_top < MODE_STACK_SIZE - 1) {
        mode_stack[++mode_stack_top] = mode;
    }
}

ModeType pop_mode() {
    if (mode_stack_top >= 0) {
        return mode_stack[mode_stack_top--];
    }
    return MODE_BASE;  // Default fallback
}

void terminate() {
    if (trace_file) {
        fclose(trace_file);
        trace_file = NULL;
    }
    printf("🛑 Shutting down Ophiuchus...\n");
    exit(0);
}
void set_theme(const char *name) {
    if (strcmp(name, "classic") == 0) current_theme = 0;
    else if (strcmp(name, "glyphs") == 0) current_theme = 1;
    else if (strcmp(name, "emoji") == 0) current_theme = 2;
    else if (strcmp(name, "debug") == 0) current_theme = 3;
    else {
        printf("🎨 Unknown theme: %s\n", name);
        return;
    }

    const char *themes[] = {"Classic", "Glyphs", "Emoji", "Debug"};
    printf("🎨 Theme set to: %s\n", themes[current_theme]);
}

void auto_heal_check() {
    int corruption_found = 0;
    for (int i = 0; i < 100; i++) {  // Scan first 100 memory slots
        if (memory[i] == 0xFF) {
            corruption_found = 1;
            break;
        }
    }

    if (corruption_found) {
        printf("⚠️  Corruption detected! Auto-restoring...\n");
        load_snapshot("auto_backup.oph");
    }
}

void auto_snapshot() {
    save_snapshot("auto_backup.oph");
    printf("💾 Auto-snapshot saved.\n");
}

void display_stack() {
    if (sp < 0 || sp > STACK_SIZE) {
        printf("⚠️  Stack pointer invalid: %d\n", sp);
        return;
    }

    printf("📦 Stack (%d items):\n", sp);
    for (int i = 0; i < sp; i++) {
        printf("[%02d] %d\n", i, stack[i]);
    }
    
    if (current_theme == 2) {
        printf("📦 Stack (%d items):\n", sp);
    } else if (current_theme == 1) {
        printf("🜍 Stack [glyph-mode]:\n");
    } else if (current_theme == 3) {
        printf("[DEBUG] stack pointer = %d\n", sp);
    } else {
        printf("Stack:\n");
    }

    for (int i = 0; i < sp; i++) {
        if (current_theme == 2) printf("[%02d] 🔹 %02X\n", i, stack[i]);
        else printf("[%02d] %02X\n", i, stack[i]);
    }
}

void show_pointer() {
    if (pointer < 0 || pointer >= MEM_SIZE) {
        printf("⚠️  Pointer out of bounds: %d\n", pointer);
        return;
    }

    printf("📍 Pointer: %d\n", pointer);
    printf("🔢 Value:   %d\n", memory[pointer]);
}

int safe_stack_push(uint8_t value) {
    if (sp >= STACK_SIZE) {
        printf("⚠️  [ERROR] Stack overflow: sp=%d\n", sp);
        return 0;  // false
    }
    stack[sp++] = value;
    return 1;  // success
}

int safe_stack_pop(uint8_t *out) {
    if (sp <= 0) {
        printf("⚠️  [ERROR] Stack underflow\n");
        return 0;  // false
    }
    *out = stack[--sp];
    return 1;  // success
}

void run_tree() {
    printf("\n🌳 Neuron Tree Stack View:\n");

    if (sp == 0) {
        printf("🧠 [empty]\n");
        return;
    }

    for (int i = 0; i < sp; i++) {
        printf("[%02d] ●", i);

        // Optional: Add symbolic representation
        uint8_t val = stack[i];
        if (val >= 1 && val <= 12) {
            // Map to a known glyph (simplified)
            const char* glyphs[] = { "☉", "☽", "🜁", "🜃", "🜄", "🜂", "🝗", "🜏", "🝰", "⛢", "☿", "🜍" };
            printf(" ─ %s", glyphs[val - 1]);
        } else {
            printf(" ─ %02X", val);
        }

        printf("\n");
    }
    printf("\n");
}

void encrypt_sensitive_data() {
    if (encryption_level >= 1) {
        for (int i = SECTOR_RITUAL_SPACE_START; i < SECTOR_DREAM_BUFFER_START; i++) {
            memory[i] ^= 0x5A;  // Simple XOR encryption
        }
    }
    if (encryption_level >= 2) {
        for (int i = SECTOR_DREAM_BUFFER_START; i < SECTOR_ORACLE_LOGS_START; i++) {
            memory[i] ^= 0xA5;
        }
    }
    if (encryption_level == 3) {
        for (int i = 0; i < MEM_SIZE; i++) {
            memory[i] ^= 0xFF;
        }
    }
}

void wrap_pointer() {
    if (pointer < 0) pointer = 0;
    else if (pointer >= MEM_SIZE) pointer = pointer % MEM_SIZE;
}

void poke_memory(int address, int value) {
    if (address >= 0 && address < MEM_SIZE) {
        memory[address] = value % 256;
        printf("Poked memory[%d] = %d\n", address, memory[address]);
    } else {
        printf("Error: Address %d out of range.\n", address);
    }
}

void peek_memory(int address) {
    if (address >= 0 && address < MEM_SIZE) {
        printf("memory[%d] = %d\n", address, memory[address]);
    } else {
        printf("Error: Address %d out of range.\n", address);
    }
}

void reset_interpreter() {
    memset(memory, 0, MEM_SIZE);   // Clear all memory
    pointer = 0;                   // Reset pointer
    sp = 0;                        // Clear stack
    aeon_state = 0;                // Reset Aeon state
    glyph_mode = 0;                // Turn off glyph mode
    trace_enabled = 0;
    trace_file = NULL;
    for (int i = 0; i < 256; i++) profile[i] = 0;
    for (int i = 0; i < MEM_SIZE; i++) frozen[i] = 0;

    printf("System memory cleared. Ready to begin again.\n");
}


void save_memory(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        perror("⚠️  Could not open file for writing");
        return;
    }

    size_t written = fwrite(memory, 1, MEM_SIZE, f);
    fclose(f);

    if (written != MEM_SIZE) {
        printf("⚠️  Incomplete memory save: %zu bytes written\n", written);
    } else {
        printf("💾 Memory saved to %s (%zu bytes)\n", filename, written);
    }
}

void load_memory(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("⚠️  Could not open file for reading");
        return;
    }

    size_t read = fread(memory, 1, MEM_SIZE, f);
    fclose(f);

    if (read != MEM_SIZE) {
        printf("⚠️  Incomplete memory load: %zu bytes read\n", read);
        // Optionally zero remaining memory
        memset(memory + read, 0, MEM_SIZE - read);
    } else {
        printf("📖 Memory loaded from %s (%zu bytes)\n", filename, read);
    }
}

void save_snapshot(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        perror("⚠️ Could not save snapshot");
        return;
    }

    fwrite(memory, 1, MEM_SIZE, f);
    fwrite(&pointer, sizeof(pointer), 1, f);
    fwrite(stack, sizeof(uint8_t), STACK_SIZE, f);
    fwrite(&sp, sizeof(sp), 1, f);
    fwrite(&aeon_state, sizeof(aeon_state), 1, f);
    fwrite(&glyph_mode, sizeof(glyph_mode), 1, f);

    fclose(f);
    printf("📸 Snapshot saved to %s\n", filename);
}

void load_snapshot(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("⚠️ Could not load snapshot");
        return;
    }

    fread(memory, 1, MEM_SIZE, f);
    fread(&pointer, sizeof(pointer), 1, f);
    fread(stack, sizeof(uint8_t), STACK_SIZE, f);
    fread(&sp, sizeof(sp), 1, f);
    fread(&aeon_state, sizeof(aeon_state), 1, f);
    fread(&glyph_mode, sizeof(glyph_mode), 1, f);

    fclose(f);
    printf("📖 Snapshot loaded from %s\n", filename);
}

void inspect_snapshot(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("⚠️  Could not open %s\n", filename);
        return;
    }

    // Skip memory
    fseek(f, MEM_SIZE, SEEK_CUR);

    // Stack buffer to read
    uint8_t temp_stack[STACK_SIZE];
    fread(temp_stack, sizeof(uint8_t), STACK_SIZE, f);

    int temp_sp = 0, temp_aeon = 0, temp_glyph = 0;
    fread(&temp_sp, sizeof(temp_sp), 1, f);
    fread(&temp_aeon, sizeof(temp_aeon), 1, f);
    fread(&temp_glyph, sizeof(temp_glyph), 1, f);

    printf("📜 Snapshot: %s\n", filename);
    printf("- Pointer:        %d\n", pointer);
    printf("- Stack Size:     %d\n", temp_sp);
    printf("- Glyph Mode:     %s\n", temp_glyph ? "ON" : "OFF");
    printf("- Aeon State:     %d\n", temp_aeon);

    fclose(f);
}

void export_environment(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        printf("❌ Failed to create export file.\n");
        return;
    }

    fwrite(memory, sizeof(uint8_t), MEM_SIZE, f);
    fwrite(stack, sizeof(uint8_t), STACK_SIZE, f);
    fwrite(&sp, sizeof(sp), 1, f);
    fwrite(&aeon_state, sizeof(aeon_state), 1, f);
    fwrite(&glyph_mode, sizeof(glyph_mode), 1, f);

    fclose(f);
    printf("📦 Environment exported to %s\n", filename);
}

void view_sector(const char *sector) {
    int start = 0, end = 0;

    if (strcmp(sector, "glyphs") == 0) {
        start = SECTOR_CORE_GLYPHS_START; end = SECTOR_RITUAL_SPACE_START;
    } else if (strcmp(sector, "rituals") == 0) {
        start = SECTOR_RITUAL_SPACE_START; end = SECTOR_DREAM_BUFFER_START;
    } else if (strcmp(sector, "dream") == 0) {
        start = SECTOR_DREAM_BUFFER_START; end = SECTOR_ORACLE_LOGS_START;
    } else if (strcmp(sector, "oracle") == 0) {
        start = SECTOR_ORACLE_LOGS_START; end = SECTOR_ELEMENTAL_FLUX_START;
    } else if (strcmp(sector, "elemental") == 0) {
        start = SECTOR_ELEMENTAL_FLUX_START; end = SECTOR_FREE_MEMORY_START;
    } else {
        printf("⚠️ Unknown sector: %s\n", sector);
        return;
    }

    printf("🔍 Viewing sector '%s' (%d - %d):\n", sector, start, end-1);
    for (int i = start; i < start + 10; i++) {
        printf("[%d] = %d\n", i, memory[i]);  // Show first 10 entries
    }
}

void auto_snapshot_on_event(const char *event) {
    char filename[64];
    snprintf(filename, sizeof(filename), "auto_%s.oph", event);
    save_snapshot(filename);
    printf("💾 Auto-snapshot triggered by '%s'\n", event);
}
