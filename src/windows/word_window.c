#include "word_window.h"
#include "sets.h"

static Window *s_word_window;
static TextLayer *s_word_layer, *s_meaning_layer, *s_word_index_layer;
static StatusBarLayer *s_status_bar_layer;
static int current_word_index = 0;
static int current_set_index = 0;
#define SET_PROGRESS_KEY 100  



static void display_word() {
    VocabSet *set = &all_sets[current_set_index];
    if (current_word_index >= 0 && current_word_index < set->totalWords) {
        static char index_buffer[32];
        snprintf(index_buffer, sizeof(index_buffer), "%d/%d", current_word_index + 1, set->totalWords);
        text_layer_set_text(s_word_index_layer, index_buffer);

        text_layer_set_text(s_word_layer, set->words[current_word_index].word);
        text_layer_set_text(s_meaning_layer, set->words[current_word_index].meaning);

        layer_set_hidden(text_layer_get_layer(s_meaning_layer), true);
    }
}

static void toggle_meaning_visibility() {
    bool is_hidden = layer_get_hidden(text_layer_get_layer(s_meaning_layer));
    layer_set_hidden(text_layer_get_layer(s_meaning_layer), !is_hidden);

    if (is_hidden) {
        VocabSet *set = &all_sets[current_set_index];
        if (!set->words[current_word_index].read) {
            set->words[current_word_index].read = true;
            set->wordsRead++;

            persist_write_data(SET_PROGRESS_KEY + current_set_index, set, sizeof(VocabSet));
        }
    }
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    toggle_meaning_visibility();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    if (current_word_index > 0) {
        current_word_index--;
        display_word();
      //  save_last_word_index();
    }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    VocabSet *set = &all_sets[current_set_index];
    if (current_word_index < set->totalWords - 1) {
        current_word_index++;
        display_word();
       // save_last_word_index();
    }
}

static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void word_window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    s_status_bar_layer = status_bar_layer_create();
    layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar_layer));

    int status_bar_height = STATUS_BAR_LAYER_HEIGHT;

    s_word_index_layer = text_layer_create(GRect(0, status_bar_height, bounds.size.w, 20));
    text_layer_set_text_alignment(s_word_index_layer, GTextAlignmentCenter);
    layer_add_child(window_layer, text_layer_get_layer(s_word_index_layer));

    int word_layer_y = status_bar_height + 20;
    s_word_layer = text_layer_create(GRect(0, word_layer_y, bounds.size.w, 40)); 
    text_layer_set_text_alignment(s_word_layer, GTextAlignmentCenter);
    text_layer_set_font(s_word_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD)); 
    layer_add_child(window_layer, text_layer_get_layer(s_word_layer));

    int meaning_layer_y = word_layer_y + 40;
    s_meaning_layer = text_layer_create(GRect(0, meaning_layer_y, bounds.size.w, bounds.size.h - meaning_layer_y)); 
    text_layer_set_text_alignment(s_meaning_layer, GTextAlignmentCenter);
    layer_add_child(window_layer, text_layer_get_layer(s_meaning_layer));

    window_set_click_config_provider(window, click_config_provider);

    display_word();
}

static void word_window_unload(Window *window) {
    text_layer_destroy(s_word_index_layer);
    text_layer_destroy(s_word_layer);
    text_layer_destroy(s_meaning_layer);
    status_bar_layer_destroy(s_status_bar_layer);
    window_destroy(s_word_window);
    s_word_window = NULL;
}

void word_window_push(int setIndex) {
    current_set_index = setIndex;
    current_word_index = 0;

    if (!s_word_window) {
        s_word_window = window_create();
        window_set_window_handlers(s_word_window, (WindowHandlers) {
            .load = word_window_load,
            .unload = word_window_unload,
        });
    }
    window_stack_push(s_word_window, true);
}


