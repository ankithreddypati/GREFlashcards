#pragma once

#include <pebble.h>

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
    VocabWord *words;  
    int wordsRead;
    int totalWords;
} VocabSet;

extern VocabSet all_sets[MAX_SETS];  

void sets_window_push();

extern const int NUM_SETS;


