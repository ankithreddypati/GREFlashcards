#pragma once

#include <pebble.h>

// Define the maximum number of sets
#define MAX_SETS 10
#define SET_LAST_WORD_KEY_BASE 200

//void load_set_progress();

typedef struct {
    char *word;
    char *meaning;
    bool read;
} VocabWord;

typedef struct {
    char *setName;
    VocabWord *words;  // Pointer to an array of VocabWord
    int wordsRead;
    int totalWords;
} VocabSet;

extern VocabSet all_sets[MAX_SETS];  // Declare the array after the type definition

// Function to push the sets window onto the window stack
void sets_window_push();

extern const int NUM_SETS;


// Additional functions or structures can be declared here if needed
