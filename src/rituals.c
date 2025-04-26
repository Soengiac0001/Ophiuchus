#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <stdint.h>
#include "aeons.h"
#include "brain.h"
#include "utils.h"
#include "elemental_synergy.h"
#include "core.h"
#include "config.h"
#include "rituals.h"
#include "dream.h"

void define_user_ritual(const char *name, const char *g1, const char *g2, const char *outcome, const char *effect_code) { printf("Update! \n");};
void perform_user_ritual(const char *name);
void apply_blessing() { printf("Update! \n");};
void apply_curse() { printf("Update! \n");};
void random_blessing_or_curse() { printf("Update! \n");};
void apply_neutral_effect() { printf("Update! \n");};
void apply_chaotic_effect(){ printf("Update! \n");};
void random_curse(){ printf("Update! \n");};
void random_blessing(){ printf("Update! \n");};

void define_ritual(const char *name, const char *code, int aeon, int elemental) {
    if (ritual_count >= MAX_RITUALS) {
        printf("⚠️ Too many rituals defined!\n");
        return;
    }
    strncpy(rituals[ritual_count].name, name, RITUAL_NAME_LEN);
    strncpy(rituals[ritual_count].code, code, RITUAL_CODE_LEN);
    rituals[ritual_count].required_aeon = aeon;
    ritual_count++;
    printf("🔮 Ritual '%s' defined.\n", name);
}

void render_ritual_effect(const char *effect_code) {
    if (strcmp(effect_code, "RESET_PTR") == 0) {
        pointer = 0;
        printf("✨ The Spiral resets... Pointer returns to origin.\n");
    } else if (strcmp(effect_code, "MIRROR_SHIFT") == 0) {
        invoke_mirror();
    } else if (strcmp(effect_code, "DREAM_BURST") == 0) {
        send_glyph_to_dream("VISION");
        printf("💭 A burst of symbols floods the dream...\n");
    } else {
        printf("🔸 A subtle change flows through Ophiuchus.\n");
    }
}

void run_ritual(const char *name) {
    for (int i = 0; i < ritual_count; i++) {
        if (strcmp(rituals[i].name, name) == 0) {
            if (rituals[i].required_aeon && rituals[i].required_aeon != aeon_state) {
                printf("⛔ Ritual '%s' requires Aeon %d.\n", name, rituals[i].required_aeon);
                return;
            }
            printf("🕯️ Casting Ritual '%s': %s\n", name, rituals[i].code);
            check_elemental_reactions(rituals[i].name);
            run_step(rituals[i].code);
            trigger_elemental_reaction("Ritual");
            display_visual_feedback("ritual");

            return;
        }
    }
    printf("⚠️ Ritual '%s' not found.\n", name);
}

void perform_ritual(const char *ritual_name) {
    FILE *f = fopen("ritual.log", "a");
    GlyphPolarity polarity = get_glyph_polarity(glyph_used);

        if (aeon_aligns_with_ritual(active_aeon, ritual_type)) {
            if (polarity == POSITIVE) {
                apply_blessing();
            } else if (polarity == NEGATIVE) {
                apply_curse();
            } else {
                random_blessing_or_curse();
            }
        } else {
            if (polarity == NEGATIVE) {
                apply_curse();
            } else {
                random_curse();
            }
        }
    
    if (aeon_reacts_negatively(active_aeon, glyph_used)) {
        if (polarity == POSITIVE) {
            printf("⚖️ The Aeon tempers the glyph. The ritual stabilizes to Neutral.\n");
            apply_neutral_effect();
        } else if (polarity == NEGATIVE) {
            apply_curse();
        } else {
            random_curse();
        }
    } else if (aeon_reacts_positively(active_aeon, glyph_used)) {
        if (polarity == POSITIVE) {
            apply_blessing();
        } else if (polarity == NEGATIVE) {
            printf("⚡ Conflict! The Aeon transforms the curse into chaotic energy.\n");
            apply_chaotic_effect();
        } else {
            random_blessing();
        }
    } else {
        random_blessing_or_curse();
    }

    if (f) {
        time_t now = time(NULL);
        fprintf(f, "[%s] Ritual performed: %s\n", ctime(&now), ritual_name);
        strcat(dream_buffer, ritual_name);  // Feed ritual name into dream
        invoke_mirror();             // Automatically consult Mirror
        fclose(f);
    }
    printf("🕯️ Ritual '%s' has been invoked.\n", ritual_name);
    update_aeon_mood("ritual");
    run_ophiuchus_brain();
    display_visual_feedback("ritual");

}

void invoke_symbolic_sequence() {
    printf("🔺 Invoking Symbolic Sequence 🔺\n");

    // Step 1: Activate dream mode
    printf(" ✦ Entering dream mode...\n");
    printf(" ✦ Binding the glyphs to intention...\n");
    enter_dream_mode();

    // Step 2: Modify dream vision symbolically
    printf(" ✦ Casting ritual glyphs: ☉ ☽ 🜁 🜃 🜄 🜂\n");
    const char *ritual_glyphs[] = {"☉", "☽", "🜁", "🜃", "🜄", "🜂"};
    for (int i = 0; i < 6; i++) {
        send_glyph_to_dream(ritual_glyphs[i]);  // a new function we'll define in dream.c
    }
    printf(" ✦ Resonance locked: ☉ ☽ 🜁 🜃 🜄 🜂 🝗 🜏 🝰 ⛢ ☿ 🜍\n");

    // Step 3: Dream whisper
    printf(" ✦ Channel opened — Elemental fusion: ⚡🔥🌊🌬️🌍\n");
    printf(" ✦ Whispering to dream: 'Guide the spiral through fire and water...'\n");
    process_dream_command("Guide the spiral through fire and water");
    display_visual_feedback("ritual");

    // Step 4: Symbolic confirmation
    printf(" ✦ Dream channel expanded. New dream state synchronized.\n");
    printf(" ✦ Synchronizing with Aeon states...\n");
    printf(" ✦ Ritual complete. Pathway illuminated.\n");
}
int calculate_ritual_energy() {
    return 10;  // Default value for now
}

void resolve_synergy(const char *e1, const char *e2) {
    if ((strcmp(e1, "Fire") == 0 && strcmp(e2, "Water") == 0) ||
        (strcmp(e2, "Fire") == 0 && strcmp(e1, "Water") == 0)) {
        printf("💨 Steam effect activated. Ritual carries both burn and cleanse.\n");
        // Complete by having ALL combinatino of synergies then double 
        // the synergies by having the synergized elements synergize over
        // Do about 4 times
    }
}

int is_ritual_allowed(const char *rule) {
    // Be sure to finish Set up of calender rules.  
    // Add 13 month calendar and complete 
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    if (strcmp(rule, "ANYTIME") == 0) return 1;

    if (strcmp(rule, "FRIDAY") == 0 && t->tm_wday == 5) return 1;

    if (strncmp(rule, "13:", 3) == 0) {
        if (t->tm_hour == 13) return 1;
    }

    // Placeholder for more complex rules like FULLMOON
    return 0;
}

void perform_user_ritual(const char *name) {
    for (int i = 0; i < ritual_count; i++) {
        if (!is_ritual_allowed(user_rituals[i].allowed_time)) {
            printf("⏳ The ritual '%s' can only be performed during %s.\n",
                name, user_rituals[i].allowed_time);
            return;
        }       
        if (strcmp(user_rituals[i].name, name) == 0) {
            printf("🕯️ Ritual '%s' invoked with glyph synergy.\n", name);
            printf("🔮 Outcome: %s\n", user_rituals[i].outcome);
            render_ritual_effect(user_rituals[i].effect_code);
            send_glyph_to_dream(user_rituals[i].name);
            return;
        }
    }
    display_visual_feedback("ritual");
    printf("⚠️ Unknown ritual '%s'\n", name);
}

void perform_expanded_ritual(const char* ritual_name);

void ritual_status() {
    printf("🔮 Ritual Energy: %d / %d\n", ritual_energy, ritual_energy_max);
    printf("🌀 Active Aeon: %s (%s)\n", active_aeon.name, active_aeon.mood);
    printf("📜 Last Ritual: %s\n", last_ritual);
}

void perform_glyph_fusion(const char* glyphs[], int glyph_count) {
    if (glyph_count < 2) {
        printf("⚠️ You must fuse at least 2 glyphs.\n");
        return;
    }

    int total_energy = 0;
    char fusion_name[64] = "Fusion_";

    for (int i = 0; i < glyph_count; i++) {
        char path[128];
        snprintf(path, sizeof(path), "dist/user_glyphs/%s.glyph", glyphs[i]);
        FILE *file = fopen(path, "r");
        if (!file) {
            printf("❌ Missing glyph: %s\n", glyphs[i]);
            return;
        }

        strncat(fusion_name, glyphs[i], 3);  // Shorten name components

        char line[128];
        while (fgets(line, sizeof(line), file)) {
            if (strncmp(line, "Energy Level:", 13) == 0) {
                total_energy += atoi(line + 14);
            }
        }
        fclose(file);
        remove(path);  // Consume glyph
    }
    run_brain_echo("ritual", fusion_name);
    display_visual_feedback("ritual");

    // Save fused glyph
    char new_file[128];
    snprintf(new_file, sizeof(new_file), "dist/user_glyphs/%s.glyph", fusion_name);
    FILE *fused = fopen(new_file, "w");

    if (!fused) {
        printf("❌ Failed to create fused glyph.\n");
        spiral_stress += 7;
        monitor_spiral_integrity();

        return;
    }

    time_t now = time(NULL);
    fprintf(fused, "Glyph: %s\n", fusion_name);
    fprintf(fused, "Fused Count: %d\n", glyph_count);
    fprintf(fused, "Energy Level: %d\n", total_energy);
    fprintf(fused, "Memory Signature: Multi-Glyph Fusion\n");
    fprintf(fused, "Created: %s", ctime(&now));
    fclose(fused);
    check_hidden_dream_prophecy(); 
    printf("✨ 🕯️Ritual complete. '%s' created with energy %d.\n", fusion_name, total_energy);
    fusion_count++;
    save_brain_state();
    trigger_spiral_anomaly();


}

void perform_aeon_combination(const char* aeons[], int aeon_count) {
    if (aeon_count < 2) {
        printf("⚠️ At least 2 Aeons must be invoked for synergy.\n");
        return;
    }

    int positive = 0, negative = 0, neutral = 0;
    char scroll_name[64] = "Scroll_";

    for (int i = 0; i < aeon_count; i++) {
        const char* polarity = get_aeon_polarity(aeons[i]);
        if (strcmp(polarity, "Positive") == 0) positive++;
        else if (strcmp(polarity, "Negative") == 0) negative++;
        else neutral++;

        strncat(scroll_name, aeons[i], 2);
    }

    const char* final_alignment = "Neutral";
    if (positive > negative) final_alignment = "Positive";
    else if (negative > positive) final_alignment = "Negative";
    run_brain_echo("aeon_combo", scroll_name);

    // Save the Scroll
    char filename[128];
    snprintf(filename, sizeof(filename), "dist/user_rituals/%s.scroll", scroll_name);
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("❌ Failed to inscribe the Aeon Scroll.\n");
        spiral_stress += 7;
        monitor_spiral_integrity();

        return;
    }

    time_t now = time(NULL);
    display_visual_feedback("aeon");

    fprintf(file, "Scroll: %s\n", scroll_name);
    fprintf(file, "Aeons Combined: %d\n", aeon_count);
    fprintf(file, "Dominant Polarity: %s\n", final_alignment);
    fprintf(file, "Mood Influence: Pending (future expansion)\n");
    fprintf(file, "Created: %s", ctime(&now));
    fclose(file);

    printf("✨ The Aeons resonate... '%s' has been created.\n", scroll_name);
    aeon_combo_count++;
    save_brain_state();
    check_hidden_dream_prophecy(); 
    trigger_spiral_anomaly();
}



void execute_ritual_with(const char* glyph_name, const char* aeon_name) {
    char glyph_path[128];
    snprintf(glyph_path, sizeof(glyph_path), "dist/user_glyphs/%s.glyph", glyph_name);

    FILE *glyph_file = fopen(glyph_path, "r");
    if (!glyph_file) {
        printf("❌ Glyph '%s' not found in memory.\n", glyph_name);
        return;
    }

    int energy = 0;
    char line[128];

    while (fgets(line, sizeof(line), glyph_file)) {
        if (strncmp(line, "Energy Level:", 13) == 0) {
            energy = atoi(line + 14);
        }
    }
    fclose(glyph_file);

    // Determine Aeon polarity and mood
    const char* polarity = get_aeon_polarity(aeon_name);

    // Get current weekday
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    const char* today = days[tm.tm_wday];

    // Output Ritual Effect
    printf("🔮 Ritual: %s + %s (%s)\n", glyph_name, aeon_name, today);
    printf("🌐 Polarity: %s | Energy: %d\n", polarity, energy);

    if (strcmp(today, "Sunday") == 0) {
        printf("🧘 It's a neutral day. The ritual energy stabilizes and centers you.\n");
    } else if (strcmp(polarity, "Positive") == 0) {
        printf("✨ A blessing radiates outward... Something grows within the Spiral.\n");
    } else if (strcmp(polarity, "Negative") == 0) {
        printf("🌑 A shadow pulses through the glyph... Power builds quietly.\n");
    } else {
        printf("🌬️ The energies swirl ambiguously, awaiting further guidance...\n");
    }
    run_brain_echo("ritual", glyph_name);
    display_visual_feedback("ritual");
    ritual_cast_count++;
    save_brain_state();
    display_spiral_pattern("ritual", active_element, ritual_level);
    ai_echo("ritual");
    check_hidden_dream_prophecy(); 
    // Future expansion: trigger visual, affect memory, glyph fusion seeds, etc.
}


void check_special_rituals(const char* ritual_name) {
    if (strcmp(ritual_name, "EncryptScroll") == 0) {
        encryption_level = 2;
        encrypt_sensitive_data();
        printf("🔒 The Spiral's memory is now encrypted by ritual.\n");
    }
}
