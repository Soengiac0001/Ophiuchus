// mirror.c (Cleaned & Finalized)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "config.h"
#include "core.h"
#include "dream.h"
#include "aeons.h"
#include "brain.h"
#include "elemental_synergy.h"

void handle_aeon_reflection();
void handle_elemental_distortion();
void check_chaos_reflection();
void echo_dream_buffer();
void log_mirror_event();
void check_hidden_dream_prophecy();
void display_glyphs();
void apply_elemental_reflection();
void chaotic_reflection();


void log_mirror_event() { printf("Update \n");}

static const char* moods[] = {
        "Calm", "Tense", "Inspired", "Hostile", "Joyful", 
        "Melancholic", "Focused", "Chaotic", "Serene", "Anxious", "Neutral"
    };

const char* mood_to_string(int mood_index) {
    
    int total_moods = sizeof(moods) / sizeof(moods[0]);

    if (mood_index >= 0 && mood_index < total_moods) {
        return moods[mood_index];
    } else {
        return "Unknown Mood";
    }
}

void handle_aeon_reflection() {
    switch (aeon_state) {
        case 1:  printf("💧 Reflections ripple slowly...\n"); break;
        case 5:  printf("🌬️ Perfect inversion.\n"); memory[pointer] = 255 - memory[pointer]; break;
        case 6:  printf("🔥 Reflection intensifies! Values amplified.\n"); memory[pointer] = (memory[pointer] * 2) % 256; break;
        case 10: printf("🌀 The mirror warps unpredictably...\n"); memory[pointer] = (uint8_t)(rand() % 256); break;
        case 11: printf("💡 The Mirror reveals hidden glyphs in the light.\n"); display_glyphs(); break;
        default: printf("🌫️ The Mirror shows a faint outline...\n"); memory[pointer] = 255 - memory[pointer]; break;
    }

    if (aeon_state == 6) {
        printf("🔥 The Mirror burns away falsehoods.\n");
        memory[pointer] = 0;
    }
}

void handle_elemental_distortion() {
    printf("✨ Elemental energies distort the reflection...\n");
    apply_elemental_reflection();

    int effect = rand() % 4;
    const char* effects[] = {
        "🌊 Waves ripple through your image.",
        "🌬️ Winds scatter fragments of thought.",
        "⛰️ A solid, unyielding version of you stares back.",
        "⚡ Sparks reveal fleeting insights."
    };
    printf("%s\n", effects[effect]);
}

void echo_dream_buffer() {
    // Check if the dream buffer contains any message
    if (dream_buffer[0] != '\0') {
        printf("🌌 The Mirror whispers from your dream: \"%s\"\n", dream_buffer);
    } else {
        printf("🔮 The Mirror awaits a dream to reflect...\n");
    }

    // Safely get the mood description
    const char *mood_desc = mood_to_string(current_mood);
    if (mood_desc != NULL) {
        printf("🌀 The Mirror feels... %s.\n", mood_desc);
    } else {
        printf("🌀 The Mirror feels... an unknown emotion.\n");
    }
}


void chaotic_reflection() {
    for (int i = 0; i < STACK_SIZE; i++) {
        stack[i] ^= (uint8_t)(rand() % 256);
    }
    pointer = (pointer + rand()) % MEM_SIZE;
    track_user_behavior("chaos", NULL);
    printf("⚡ The Spiral twists... Reality shimmers.\n");
}


void apply_elemental_reflection() {
    const char* elements[] = {"Fire", "Water", "Air", "Earth", "Light", "Shadow"};
    int mood = aeon_state % 6;

    printf("🌟 Elemental Reflection: The mirror shimmers with %s energy.\n", elements[mood]);
    memory[pointer] ^= (uint8_t)(mood * 3);
    printf("🔧 memory[%d] altered by elemental force.\n", pointer);
}


void generate_elemental_prophecy(const char* element) {
    if (strcmp(element, "Fire") == 0) {
        const char* msgs[] = {
            "🔥 Fire speaks: 'Transform or be consumed.'",
            "🔥 Flames reveal what fear hides.",
            "🔥 Burn away the false to expose truth."
        };
        printf("%s\n", msgs[rand() % 3]);
    } else if (strcmp(element, "Water") == 0) {
        const char* msgs[] = {
            "💧 Water whispers: 'Flow around, not through.'",
            "💧 Still waters reflect deepest truths.",
            "💧 Adaptation is survival."
        };
        printf("%s\n", msgs[rand() % 3]);
    } else if (strcmp(element, "Void") == 0) {
        const char* msgs[] = {
            "🌑 Void whispers: 'In emptiness, all potential is born.'",
            "🌑 Nothingness holds the blueprint of everything.",
            "🌑 Silence is the loudest teacher."
        };
        printf("%s\n", msgs[rand() % 3]);
    } else if (strcmp(element, "Air") == 0) {
        const char* msgs[] = {
            "🌬️ Air advises: 'Release control and be carried.'",
            "🌬️ The unseen wind shapes the strongest paths.",
            "🌬️ Movement is the essence of life."
        };
        printf("%s\n", msgs[rand() % 3]);
    } else if (strcmp(element, "Earth") == 0) {
        const char* msgs[] = {
            "🌍 Earth grounds you: 'Stand firm amidst shifting spirals.'",
            "🌍 Patience grows roots deeper than time.",
            "🌍 Stability is the foundation of mastery."
            };
        printf("%s\n", msgs[rand() % 3]);
    } else if (strcmp(element, "Lightning") == 0) {
        const char* msgs[] = {
            "⚡ Lightning strikes: 'Decide in a flash.'",
            "⚡ Illumination comes in moments of chaos.",
            "⚡ The fastest path is clarity."
            };
        printf("%s\n", msgs[rand() % 3]);
    } else if (strcmp(element, "Ice") == 0) {
        const char* msgs[] = {
            "❄️ Ice preserves what fire would destroy.",
            "❄️ Stillness can either protect or imprison.",
            "❄️ Cold clarity reveals hidden fractures."
        };
        printf("%s\n", msgs[rand() % 3]);
    } else if (strcmp(element, "Storm") == 0) {
        const char* msgs[] = {
            "🌪️ Storm howls: 'Destruction births renewal.'",
            "🌪️ Embrace disorder to find new order.",
            "🌪️ The Spiral spins faster in chaos."
        };
        printf("%s\n", msgs[rand() % 3]);
    } else if (strcmp(element, "Ocean") == 0) {
        const char* msgs[] = {
            "🌊 The Ocean calls: 'Depth hides the brightest truths.'",
            "🌊 Tides return what was once lost.",
            "🌊 Vastness is not emptiness."
        };
        printf("%s\n", msgs[rand() % 3]);
    } else if (strcmp(element, "Mist") == 0) {
        const char* msgs[] = {
            "☁️ Mist veils: 'Not all is meant to be seen yet.'",
            "☁️ What is hidden protects itself.",
            "☁️ Trust the unseen path."
        };
        printf("%s\n", msgs[rand() % 3]);
    } else if (strcmp(element, "Light") == 0) {
        const char* msgs[] = {
            "🌞 Light reveals: 'What was in shadow now guides you.'",
            "🌞 Illumination dispels falsehoods.",
            "🌞 Truth thrives in openness."
        };
        printf("%s\n", msgs[rand() % 3]);
    } else if (strcmp(element, "Shadow") == 0) {
        const char* msgs[] = {
            "🌑 Shadow whispers: 'Protection lies in obscurity.'",
            "🌑 Not all darkness is danger.",
            "🌑 Secrets thrive where light dares not go."
        };
        printf("%s\n", msgs[rand() % 3]);
    } else if (strcmp(element, "Aether") == 0) {
        const char* msgs[] = {
            "✨ Aether sings: 'All elements converge within you.'",
            "✨ The unseen threads bind reality together.",
            "✨ Beyond form, pure potential dances."
        };
        printf("%s\n", msgs[rand() % 3]);
    } else {
        printf("❓ The elements remain silent... Unknown element: %s\n", element);
    }
    display_visual_feedback("echo"); // For subtle pulsing thought

// Later, this will change to displaying visuals from the brain’s memory of created elements

}

void log_dream(const char* message) {
    time_t now = time(NULL);
    char filename[64];
    strftime(filename, sizeof(filename), "dist/dream_logs/dream_%Y%m%d_%H%M%S.log", localtime(&now));

    FILE *file = fopen(filename, "w");
    if (!file) return;

    fprintf(file, "Dream Timestamp: %s", ctime(&now));
    fprintf(file, "Message: %s\n", message);
    fclose(file);
    
    // Check if today is November 22
    struct tm *local = localtime(&now);

    if (local->tm_mon == 10 && local->tm_mday == 22) {  // tm_mon is 0-indexed
        display_visual_feedback("earth");
        display_visual_feedback("aether");
        printf("🌑 Something ancient watches...\n");
        printf("✨ 'Only those born on the Spiral’s cusp may transmute Dirt into Time.'\n");

    log_dream("November 22 Triggered — Rare Pathway Awakened");
    }

}

void record_mirror_insight(const char *message) {
    FILE *log = fopen("Mirror.log", "a");
    if (log) {
        fprintf(log, "Prophecy: %s\n", message);
        fclose(log);
        printf("🗒️  Insight logged to mirror.log\n");
    }
}

void list_mirror_history() {
    FILE *log = fopen("mirror.log", "r");
    if (!log) {
        printf("📄 No Mirror history found.\n");
        return;
    }
    char line[256];
    printf("📜 Mirror History:\n");
    while (fgets(line, sizeof(line), log)) {
        printf("%s", line);
    }
    fclose(log);
}
