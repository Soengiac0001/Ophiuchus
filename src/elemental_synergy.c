#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "elemental_synergy.h"
#include "aeons.h"
#include "glyphs.h"
#include "brain.h"
#include "utils.h"

void clear_memory_sector();
void log_new_synergy(const char*, const char*);
void track_user_behavior(const char*, const char*);
void reset_elemental_flux();
void blur_dream();
void shuffle_memory();
void spike_stack();
void freeze_ritual_energy();
void randomize_modes();
void confuse_glyphs();
void unlock_random_ritual();
void secure_memory_sector();
void invert_pointer();
void stabilize_memory();

const char* element_names[] = { "Fire", "Water", "Air", "Earth", "Aether",
    "Lightening", "Mist", "Dark", "Void", "Shadow", "Storm", "Ice", "Origin" };

void influence_by_aeon(int aeon_state) {
    // Example: Aeon of Fire boosts Fire mood
    if (aeon_state == 6) elementals[1].mood += 2;
}

SynergyPattern base_patterns[] = {
    // Fire combinations (Positive)
    {"Air+Fire",       "Wildfire"},
    {"Earth+Fire",     "Glass Shard"},
    {"Fire+Mist",      "Smoke Veil"},
    {"Fire+Aether",    "Soulflame"},
    {"Fire+Lightning", "Plasma Arc"},

    // Water combinations (Positive)
    {"Air+Water",      "Mist Veil"},
    {"Earth+Water",    "Clay"},
    {"Water+Mist",     "Healing Fog"},
    {"Water+Aether",   "Spirit Spring"},
    {"Water+Lightning","Charged Current"},

    // Shadow combinations (Negative)
    {"Earth+Shadow",   "Obsidian Core"},
    {"Mist+Shadow",    "Phantom Veil"},
    {"Shadow+Storm",   "Night Tempest"},
    {"Shadow+Void",    "Echo Fragment"},
    {"Shadow+Ice",     "Frozen Fear"},

    // Void combinations (Negative)
    {"Earth+Void",     "Hollow Stone"},
    {"Mist+Void",      "Spectral Haze"},
    {"Void+Storm",     "Abyssal Maelstrom"},
    {"Void+Ice",       "Voidfrost"},
    {"Void+Lightning", "Null Spark"},

    // Storm combinations (Negative)
    {"Earth+Storm",    "Landslide"},
    {"Mist+Storm",     "Shrouded Cyclone"},
    {"Storm+Ice",      "Blizzard Core"},

    // Lightning combinations (Negative after adjustment)
    {"Earth+Lightning","Magnetite"},
    {"Mist+Lightning", "Static Fog"},

    // Light combinations (Positive)
    {"Air+Light",      "Radiant Breeze"},
    {"Earth+Light",    "Crystal Formation"},
    {"Light+Mist",     "Halo Fog"},
    {"Light+Aether",   "Beacon Pulse"},

    // Aether combinations (Positive)
    {"Earth+Aether",   "Geo-Spirit"},
    {"Mist+Aether",    "Veil of Connection"},

    // Ice (Neutral & Negative mixes)
    {"Earth+Ice",      "Permafrost Stone"},
    {"Mist+Ice",       "Glacial Veil"},

    // Neutral-only mixes
    {"Earth+Mist",     "Foggy Terrain"},
    {"Earth+Origin",   "First Mountain"},
    {"Mist+Origin",    "Silent Shroud"},
    {"Aether+Origin",  "Ethereal Seed"}
};

void load_elemental_defaults() {
    elementals[0] = (Elemental){"Void", "Silence spreads...", 5};
    elementals[1] = (Elemental){"Fire", "Burns intensely!", 7};
    elementals[2] = (Elemental){"Water", "Flows calmly.", 6};
    elementals[3] = (Elemental){"Air", "Whispers secrets.", 5};
    elementals[4] = (Elemental){"Earth", "Stands firm.", 6};
    elementals[5] = (Elemental){"Light", "Illuminates the path.", 5};
    elementals[6] = (Elemental){"Shadow", "Conceals mysteries.", 4};
    elementals[7] = (Elemental){"Storm", "Rages unpredictably.", 8};
    elementals[8] = (Elemental){"Ice", "Freezes thoughts.", 5};
    elementals[9] = (Elemental){"Lightning", "Strikes swiftly.", 7};
    elementals[10] = (Elemental){"Aether", "Connects all things.", 6};
    elementals[11] = (Elemental){"Mist", "Obscures vision.", 5};
    elementals[12] = (Elemental){"Origin", "Begins anew.", 5};
}

void check_elemental_reactions() {
    for (int i = 0; i < 13; i++) {
        if (elementals[i].mood > 8) {
            printf("⚡ Elemental Surge: %s - %s\n", elementals[i].name, elementals[i].effect);
        }
    }
}

const char* get_day_name() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return days[tm.tm_wday];
}

void build_combo_key(const char* elements[], int count, char* out_key) {
    strcpy(out_key, elements[0]);
    for (int i = 1; i < count; i++) {
        strcat(out_key, "+");
        strcat(out_key, elements[i]);
    }
}

const char* generate_dynamic_name(const char* dominant_element, int total_power, int glyph_level) {
    static char name[128];
    const char* positive_suffixes[] = {"Blessing", "Lumina", "Ascend", "Flare"};
    const char* negative_suffixes[] = {"Bane", "Umbral", "Gloom", "Eclipse"};
    const char* neutral_suffixes[]  = {"Shard", "Veil", "Echo", "Essence"};

    int choice = rand() % 4;

    if (total_power > 0)
        snprintf(name, sizeof(name), "%s %s", dominant_element, positive_suffixes[choice]);
    else if (total_power < 0)
        snprintf(name, sizeof(name), "%s %s", dominant_element, negative_suffixes[choice]);
    else
        snprintf(name, sizeof(name), "%s %s", dominant_element, neutral_suffixes[choice]);

    if (glyph_level >= 4) {
        strcat(name, " of ");
        strcat(name, active_aeon.name);
    }
    if (glyph_level >= 5) {
        strcat(name, " under ");
        strcat(name, active_aeon.planet);
    }
    if (glyph_level == 6) {
        strcat(name, " on ");
        strcat(name, get_day_name());
    }

    if (total_power > 10) {
    spiral_stress += 5;
    monitor_spiral_integrity();
    }
    
    // If no match is found, handle dynamic generation here:
	printf("⚡ The Spiral weaves a new form...\n");

	printf("🌀 New Synergy Discovered: %s\n", name);
    
    return name;
}

int get_element_polarity(const char* element) {
    if (strcmp(element, "Fire") == 0) return 1;
    if (strcmp(element, "Water") == 0) return 1;
    if (strcmp(element, "Light") == 0) return 1;
    if (strcmp(element, "Air") == 0) return 1;
    if (strcmp(element, "Aether") == 0) return 1;

    if (strcmp(element, "Shadow") == 0) return -1;
    if (strcmp(element, "Void") == 0) return -1;
    if (strcmp(element, "Storm") == 0) return -1;
    if (strcmp(element, "Ice") == 0) return -1;
    if (strcmp(element, "Lightning") == 0) return -1;

    if (strcmp(element, "Mist") == 0) return 0;
    if (strcmp(element, "Earth") == 0) return 0;
    if (strcmp(element, "Origin") == 0) return 0;

    return 0;  // Default neutral for unknowns
}

const char* generate_synergy_result(const char* elements[], int count, int glyph_level) {
    int net_polarity = 0;
    for (int i = 0; i < count; i++) {
        net_polarity += get_element_polarity(elements[i]);
    }
    const char* today = get_day_name();
	const char* dominant_element = elements[0];
    int mood_modifier = get_aeon_mood_modifier(&active_aeon);

	if (strcmp(today, "Sunday") == 0) {
		if (net_polarity != 0) {
			printf("🌑 The Spiral resists... Positive and Negative forces falter on Sunday.\n");
			net_polarity = 0;
		} else {
		printf("🌫️ Neutral energies flourish today (+1 boost).\n");
			net_polarity += 1;
		}
	} else if ((strcmp(today, "Monday") == 0 || strcmp(today, "Tuesday") == 0 || strcmp(today, "Thursday") == 0) && net_polarity < 0) {
		net_polarity -= 1;
		printf("🖤 Negative energies empowered by the day.\n");
	} else if ((strcmp(today, "Wednesday") == 0 || strcmp(today, "Friday") == 0 || strcmp(today, "Saturday") == 0) && net_polarity > 0) {
		net_polarity += 1;
		printf("🤍 Positive energies shine brighter today.\n");
	}
	
	if (mood_modifier == 0 && strcmp(today, "Sunday") == 0) {
		mood_modifier = 2;
        printf("🌫️ Neutral energies flourish today.\n");
    }

    int total_power = net_polarity + mood_modifier;
    
    if (total_power == 0) {
        printf("%s\n", ORIGIN_PHRASE);
        return "Origin Essence";
    }
    
    if (total_power > 10) {
    spiral_stress += 5;
    monitor_spiral_integrity();
    }

    char combo_key[256] = "";
    build_combo_key(elements, count, combo_key);

    for (int i = 0; i < BASE_PATTERN_COUNT; i++) {
        if (strcmp(combo_key, base_patterns[i].combo_key) == 0) {
            return base_patterns[i].result;
        }
    }

    printf("⚡ The Spiral weaves a new form...\n");
    const char* dynamic_result = generate_dynamic_name(dominant_element, total_power, glyph_level);
    log_new_synergy(combo_key, dynamic_result);
    printf("🌀 New Synergy Discovered: %s\n", dynamic_result);
	
    if (strcmp(elements[0], "Water") == 0 || strcmp(elements[1], "Water") == 0) {
	track_user_behavior("element", "Water");
    }
    if (strcmp(elements[0], "Storm") == 0 || strcmp(elements[1], "Storm") == 0) {
	track_user_behavior("element", "Storm");
    }
    
    display_spiral_pattern("synergy", dominant_element, total_power);
    track_user_behavior("element", dominant_element);
    printf("⚡ Synergy Result: %s (Power %d)\n", dynamic_result, total_power);
    trigger_spiral_anomaly();
    
    return dynamic_result;

}

void log_new_synergy(const char* combo_key, const char* result) {
    FILE* file = fopen("synergy_log.txt", "a");
    if (!file) return;
    fprintf(file, "%s => %s\n", combo_key, result);
    fclose(file);
}

void clear_recent_synergies() {
    printf("🔗 Residual elemental tensions released.\n");
    // If you track recent synergies, reset them here
}

void trigger_elemental_reaction(const char* context) {
    int element = rand() % 13;

    switch (element) {
        case 0: printf("🌑 Void envelops the system...\n"); clear_memory_sector(); break;
        case 1: printf("🔥 Fire sparks chaotic energy!\n"); corrupt_stack(); break;
        case 2: printf("💧 Water soothes volatile data.\n"); stabilize_memory(); break;
        case 3: printf("🌬️ Air shifts pointer direction.\n"); invert_pointer(); break;
        case 4: printf("🌍 Earth fortifies memory sectors.\n"); secure_memory_sector(); break;
        case 5: printf("🌞 Light reveals hidden rituals.\n"); unlock_random_ritual(); break;
        case 6: printf("🌑 Shadow obscures glyph meanings.\n"); confuse_glyphs(); break;
        case 7: printf("🌪️ Storm scrambles active modes.\n"); randomize_modes(); break;
        case 8: printf("❄️ Ice freezes ritual energy gain.\n"); freeze_ritual_energy(); break;
        case 9: printf("⚡ Lightning overloads the stack.\n"); spike_stack(); break;
        case 10: printf("✨ Aether warps memory layout.\n"); shuffle_memory(); break;
        case 11: printf("☁️ Mist veils dream clarity.\n"); blur_dream(); break;
        case 12: printf("🌀 Origin resets elemental balance.\n"); reset_elemental_flux(); break;
        update_aeon_mood("element");
    }

    // Echoes
    append_to_dream("🌫️ An elemental force ripples through the Spiral...");
    adjust_aeon_emotion(element_names[element]);
    influence_brain_soul(element_names[element]);
}
