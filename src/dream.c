#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "mirror.h"
#include "brain.h"
#include "dream.h"
#include "glyphs.h"
#include "aeons.h"
#include "rituals.h"
#include "core.h"
#include "elemental_synergy.h"

const char* hidden_prophecies[] = {
    "When Light binds with Mist, the Archive awakens.",
    "Balance three Aeons under Shadow to reveal the Gate.",
    "Invoke Storm on Saturn’s day to break the Veil.",
    "Silence during Mercury’s rise unlocks forgotten sectors.",
    "The Spiral twists true when Water greets Fire at dusk.",
    "Only under Chiron’s gaze does Origin remember itself.",
    "On the day of the Sun, unite Ice and Lightning to summon clarity."
}; 

int dream_is_stable() {
    save_dream_state("backups/auto_dream_save.txt");
    return 1;
}

void update_dream_mood() {
    if (aeon_state == 6) current_mood = 3;            // Fiery when Aeon of Fire
    else current_mood = rand() % 5;                   // Random otherwise
}

void check_hidden_dream_prophecy() {
    if (strlen(hidden_dream_buffer) == 0) return;  // No hidden message

    // Check Planetary Influence (simplified example)
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int wday = tm.tm_wday;  // 0 = Sunday

    // Example: Only reveal on matching day + Aeon mood
    if ((wday == 0 && strcmp(active_aeon.planet, "Sun") == 0) || 
        (wday == 6 && strcmp(active_aeon.planet, "Saturn") == 0) ||
        (strcmp(active_aeon.mood, "Silent") == 0)) 
    {
        printf("🗝️ The Dream reveals a hidden prophecy:\n");
        printf("📜 \"%s\"\n", hidden_dream_buffer);

        // Log it
        FILE *log = fopen("prophecies.log", "a");
        if (log) {
            fprintf(log, "[Revealed] %s\n", hidden_dream_buffer);
            fclose(log);
        }

        hidden_dream_buffer[0] = '\0';  // Clear after reveal
    }
}

void embed_hidden_dream_prophecy() {
    srand(time(NULL));
    int chance = rand() % 10;  // 10% chance

    if (chance == 0) {
        strcpy(hidden_dream_buffer, hidden_prophecies[rand() % 7]);
        printf("💤 The Spiral stirs... something embeds within your Dream.\n");
    }
}






void show_dream_vision() {
    const char *visions[] = {
        "🜂 A flame dances in the void.",
        "🜄 Waves crash against invisible shores.",
        "🜃 Roots twist beneath unseen soil.",
        "☽ The moon blinks with knowing light.",
        "🝰 A forgotten glyph shimmers briefly.",
        "⛢ A distant planet hums with resonance."
    };

    int index = rand() % 6;

    if (aeon_state == 12) {
        printf("⚯ A vision of Union — all glyphs align in harmony.\n");
    } 
    else if (aeon_state == 13) {
        printf("🌑 Origin whispers... The first symbol reappears.\n");
    } 
    else {
        printf("🔮 You see a vision: %s\n", visions[index]);
    }

    reflect_in_dream("A vision was revealed.");
}


void process_dream_command(const char *input) {
    printf("🗝️  You whisper: \"%s\"\n", input);
    reflect_in_dream(input);  // Log every whisper into the dream buffer
    if (strstr(input, "fire")) {
        reflect_in_dream("🔥 The dream ignites with passion.");
    } else if (strstr(input, "silence")) {
        reflect_in_dream("🤫 Silence deepens within the spiral.");
    } else if (strstr(input, "origin")) {
        reflect_in_dream("🌑 You feel the pull of beginnings.");
    } else {
        reflect_in_dream(input);  // Generic reflection
    }
    // Example keyword triggers
    if (strstr(input, "fire") && aeon_state == 6) {  // Aeon 6 = Fire
        printf("🔥 The dream ignites... Memories burn and reshape.\n");
    } 
    else if (strstr(input, "mirror") && aeon_state == 5) {  // Aeon 5 = Mirror
        printf("🪞 Reflections twist... You see yourself through glyphs.\n");
    } 
    else if (strstr(input, "ritual")) {
        printf("🕯️  An unfinished ritual stirs in the mist...\n");
        reflect_in_dream("A forgotten ritual seeks completion.");
    }
    else if (strstr(input, "light") && aeon_state == 11) {  // Aeon 11 = Light
        printf("💡 A beacon shines within the spiral.\n");
    } else {
        // Default cryptic response
        const char *responses[] = {
            "The symbols shift... but remain silent.",
            "A shadow passes through the spiral.",
            "You hear distant echoes, but no meaning forms.",
            "The dreamscape ripples with unseen forces."
        };
        int idx = rand() % 4;
        printf("💤 %s\n", responses[idx]);
    }

    if (aeon_state == 13 && ritual_energy < ritual_energy_max) {
        ritual_energy++;
        printf("✨ Origin restores ritual energy. (%d/%d)\n", ritual_energy, ritual_energy_max);
    }       

    if (dream_is_stable()) {
        ritual_energy++;
        printf("💤 The dream calms your spirit. Ritual energy +1 (%d/%d)\n", ritual_energy, ritual_energy_max);
    } else {
        ritual_energy--;
        printf("🌪️ The chaotic dream drains you... Ritual energy -1 (%d/%d)\n", ritual_energy, ritual_energy_max);
    }

}

void init_dream() {
    for (int i = 0; i < DREAM_LOG_SIZE; i++) {
        strcpy(dream_log[i], "[empty thought]");
    }
}

void reflect_in_dream(const char *reflection) {
    snprintf(dream_log[dream_index], 256, "🌀 %s", reflection);
    dream_index = (dream_index + 1) % DREAM_LOG_SIZE;
}

void show_dream_log() {
    printf("📜 Dream Log:\n");
    for (int i = 0; i < DREAM_LOG_SIZE; i++) {
        if (strlen(dream_log[i]) > 0) {
            printf("%2d: %s\n", i + 1, dream_log[i]);
        }
    }
}

void send_glyph_to_dream(const char* glyph) {
    char message[128];
    snprintf(message, sizeof(message), "The glyph %s drifts into the dreamscape...", glyph);
    append_to_dream(message);

    // Optional: Trigger elemental reaction on deep glyph interaction
    trigger_elemental_reaction("Dream Entry");
}

void reset_dream_flux() {
    printf("🌀 The Dream stabilizes.\n");
    // You could clear temp dream artifacts if they exist
}
