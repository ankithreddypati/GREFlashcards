#include "sets.h"
#include  "word_window.h"

static Window *s_main_window;
static MenuLayer *s_menu_layer;
static StatusBarLayer *s_status_layer;

// #define NUM_SETS 10
const int NUM_SETS = 10; // Only define it here


// Declare an array of VocabSet
VocabSet all_sets[MAX_SETS]; 


static void initialize_sets() {
    for (int i = 0; i < NUM_SETS; i++) {
        all_sets[i].setName = malloc(sizeof(char) * 16); // Allocate space for set name
        snprintf(all_sets[i].setName, 16, "Set %d", i + 1);
        all_sets[i].totalWords = 10; // Fixed number of words in each set
        all_sets[i].wordsRead = 0;

        // Allocate memory for words
        all_sets[i].words = malloc(sizeof(VocabWord) * all_sets[i].totalWords);

        // Initialize words for each set (example for the first 3 sets)
        if (i == 0) {
            all_sets[i].words[0] = (VocabWord){"Abate", "To decrease; reduce", false};
            all_sets[i].words[1] = (VocabWord){"Tenacity", "The quality or fact of being very determined; determination", false};
            // ... Initialize other words for Set 1 ...
        } else if (i == 1) {
            all_sets[i].words[0] = (VocabWord){"adulterate", "render (something) poorer in quality by adding another substance.", false};
            all_sets[i].words[1] = (VocabWord){"advocate", "a person who publicly supports or recommends a particular cause or policy.", false};
            all_sets[i].words[2] = (VocabWord){"aggrandize", "increase the power, status, or wealth of.", false};
            all_sets[i].words[3] = (VocabWord){"alacrity", "brisk and cheerful readiness.", false};
            all_sets[i].words[4] = (VocabWord){"ambivalent", "having mixed feelings or contradictory ideas about something or someone.", false};
            all_sets[i].words[5] = (VocabWord){"ameliorate", "make (something bad or unsatisfactory) better.", false};
        } else if (i == 2) {
            all_sets[i].words[0] = (VocabWord){"Aggrandize", "Increase power or wealth", false};
            // ... Initialize other words for Set 3 ...
        }
        
    }
}




static uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
    return NUM_SETS;
}

static void menu_draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *context) {
    VocabSet *set = &all_sets[cell_index->row];

    // Prepare the set name string
    static char name_buffer[32];
    snprintf(name_buffer, sizeof(name_buffer), "%s", set->setName);

    // Prepare the progress string
    static char progress_buffer[32];
    snprintf(progress_buffer, sizeof(progress_buffer), "%d/%d", set->wordsRead, set->totalWords);

    // Set the fonts
    GFont name_font = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
    GFont progress_font = fonts_get_system_font(FONT_KEY_GOTHIC_18);

    // Draw the set name
    graphics_draw_text(ctx, name_buffer, name_font, 
                       GRect(3, -3, layer_get_bounds(cell_layer).size.w, 28), 
                       GTextOverflowModeTrailingEllipsis, 
                       GTextAlignmentLeft, NULL);

    // Draw the progress text aligned to the right
    graphics_draw_text(ctx, progress_buffer, progress_font, 
                       GRect(3, -1, layer_get_bounds(cell_layer).size.w - 6, 24), 
                       GTextOverflowModeTrailingEllipsis, 
                       GTextAlignmentRight, NULL);
}



static void select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
    
    // load_last_word_index(cell_index->row);

    word_window_push(cell_index->row); // Open the word window for the selected set
}

void save_last_word_index(int setIndex, int lastWordIndex) {
    int key = SET_LAST_WORD_KEY_BASE + setIndex;
    persist_write_int(key, lastWordIndex);
}

int load_last_word_index(int setIndex) {
    int key = SET_LAST_WORD_KEY_BASE + setIndex;
    if (persist_exists(key)) {
        return persist_read_int(key);
    }
    return 0; // Default to start from the beginning if no data is found
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    // Create StatusBarLayer
    s_status_layer = status_bar_layer_create();
    layer_add_child(window_layer, status_bar_layer_get_layer(s_status_layer));

    // Adjust bounds for the status bar
    GEdgeInsets insets = {.top = STATUS_BAR_LAYER_HEIGHT};
    bounds = grect_inset(bounds, insets);

    // Create MenuLayer
    s_menu_layer = menu_layer_create(bounds);
    menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks){
        .get_num_rows = get_num_rows_callback,
        .draw_row = menu_draw_row_callback,
        .select_click = select_callback
    });
    menu_layer_set_click_config_onto_window(s_menu_layer, window);
    layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

static void window_unload(Window *window) {
    menu_layer_destroy(s_menu_layer);
    status_bar_layer_destroy(s_status_layer);

    // Free dynamically allocated memory for set names
    for (int i = 0; i < NUM_SETS; i++) {
        free(all_sets[i].setName);
        free(all_sets[i].words); // Free the memory allocated for words
    }
}

void sets_window_push() {
   initialize_sets(); // Initialize sets before creating the window

    if (!s_main_window) {
        s_main_window = window_create();
        window_set_window_handlers(s_main_window, (WindowHandlers){
            .load = window_load,
            .unload = window_unload
        });
    }
    window_stack_push(s_main_window, true);
}
