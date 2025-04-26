#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "config.h"
#include "aeons.h"
#include "glyphs.h"
#include "elemental_synergy.h"

int aeon_aligns_with_ritual(AeonProfile active_aeon, RitualType ritual_type) {
    // Simple placeholder logic
    if (active_aeon.element == ritual_type) {
        return 1;  // Aligned
    }
    return 0;  // Not aligned
}

const char* get_aeon_polarity(const char* aeon_name) {
    if (strcmp(aeon_name, "Lumael") == 0 || strcmp(aeon_name, "Vorun") == 0 || strcmp(aeon_name, "Aetheriel") == 0)
        return "Negative";
    if (strcmp(aeon_name, "Thalen") == 0 || strcmp(aeon_name, "Cyrielle") == 0 || strcmp(aeon_name, "Adio") == 0)
        return "Positive";
    return "Neutral";
}

int aeon_reacts_negatively(AeonProfile aeon, const char* glyph) {
    int aeon_polarity = get_element_polarity(aeon.element);
    GlyphPolarity glyph_polarity = get_glyph_polarity(glyph);

    if (aeon_polarity > 0 && glyph_polarity == NEGATIVE) return 1;
    if (aeon_polarity < 0 && glyph_polarity == POSITIVE) return 1;

    // Special rule: Origin Aeon never reacts negatively
    if (strcmp(aeon.element, "Origin") == 0) return 0;

    return 0;
}

int aeon_reacts_positively(AeonProfile aeon, const char* glyph) {
    int aeon_polarity = get_element_polarity(aeon.element);
    GlyphPolarity glyph_polarity = get_glyph_polarity(glyph);

    if (aeon_polarity > 0 && glyph_polarity == POSITIVE) return 1;
    if (aeon_polarity < 0 && glyph_polarity == NEGATIVE) return 1;

    // Origin always reacts positively
    if (strcmp(aeon.element, "Origin") == 0) return 1;

    return 0;
}

int get_aeon_mood_modifier(const AeonProfile* aeon) {
    if (strcmp(aeon->mood, "Positive") == 0) return 1;
    if (strcmp(aeon->mood, "Negative") == 0) return -1;
    return 0;  // Neutral mood
}

void set_aeon_mood(int aeon_index, const char* new_mood) {
    if (aeon_index < 1 || aeon_index > 13) {
        printf("⚠️ Invalid Aeon index: %d\n", aeon_index);
        return;
    }

    AeonProfile* aeon = &aeons[aeon_index - 1];

    // Update mood safely
    strncpy(aeon->mood, new_mood, sizeof(aeon->mood) - 1);
    aeon->mood[sizeof(aeon->mood) - 1] = '\0';  // Null-terminate

    // Set active Aeon
    active_aeon = *aeon;

    // Feedback to user
    printf("🌙 Aeon %d (%s) mood set to '%s'.\n", aeon_index, aeon->name, aeon->mood);
    printf("🜂 Aeon %s mood shifts '%s'subtly...\n", active_aeon.name, active_aeon.mood);

}
