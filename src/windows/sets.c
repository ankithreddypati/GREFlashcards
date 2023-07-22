#include "sets.h"
#include  "word_window.h"

static Window *s_main_window;
static MenuLayer *s_menu_layer;
static StatusBarLayer *s_status_layer;

const int NUM_SETS = 10; 


VocabSet all_sets[MAX_SETS]; 


static void initialize_sets() {
    for (int i = 0; i < NUM_SETS; i++) {
        all_sets[i].setName = malloc(sizeof(char) * 16); 
        snprintf(all_sets[i].setName, 16, "Set %d", i + 1);
        all_sets[i].totalWords = 10;
        all_sets[i].wordsRead = 0;

        all_sets[i].words = malloc(sizeof(VocabWord) * all_sets[i].totalWords);

        if (i == 0) {
            all_sets[i].words[0] = (VocabWord){"Abate", "To decrease; reduce", false};
            all_sets[i].words[1] = (VocabWord){"amorphous", "without a clearly defined shape or form.", false};
            all_sets[i].words[2] = (VocabWord){"belie", "(of an appearance) fail to give a true impression of (something).", false};
            all_sets[i].words[3] = (VocabWord){"capricious", "given to sudden and unaccountable changes of mood or behavior.", false};
            all_sets[i].words[4] = (VocabWord){"cerebral", "of the cerebrum of the brain.", false};
            all_sets[i].words[5] = (VocabWord){"congenial", "pleasant or agreeable because suited to one's taste or inclination", false};
            all_sets[i].words[6] = (VocabWord){"conspicuous", "1. clearly visible. 2. attracting notice or attention.", false};
            all_sets[i].words[7] = (VocabWord){"cursory", "hasty and therefore not thorough or detailed.", false};
            all_sets[i].words[8] = (VocabWord){"daunting", "seeming difficult to deal with in prospect; intimidating.", false};
            all_sets[i].words[9] = (VocabWord){"deify", "worship or regard as a god.", false};
        } else if (i == 1) {
            all_sets[i].words[0] = (VocabWord){"didactic", "in the manner of a teacher, particularly so as to appear patronizing.", false};
            all_sets[i].words[1] = (VocabWord){"disseminate", "spread (something, especially information) widely.", false};
            all_sets[i].words[2] = (VocabWord){"feasible", "possible to do easily or conveniently.", false};
            all_sets[i].words[3] = (VocabWord){"flout", "openly disregard (a rule, law, or convention)", false};
            all_sets[i].words[4] = (VocabWord){"homogeneous", "of the same kind; alike.", false};
            all_sets[i].words[5] = (VocabWord){"humdrum", "lacking excitement or variety; boringly monotonous.", false};
            all_sets[i].words[6] = (VocabWord){"insipid", "lacking flavor; weak or tasteless.", false};
            all_sets[i].words[7] = (VocabWord){"loquacious", "tending to talk a great deal; talkative.", false};
            all_sets[i].words[8] = (VocabWord){"misanthropic", "having or showing a dislike of other people; unsociable.", false};
            all_sets[i].words[9] = (VocabWord){"misnomer", "a wrong or inaccurate name or designation.", false};
        } else if (i == 2) {
            all_sets[i].words[0] = (VocabWord){"negligent", "failing to take proper care over something.", false};
            all_sets[i].words[1] = (VocabWord){"obsequious", "obedient or attentive to an excessive or servile degree.", false};
            all_sets[i].words[2] = (VocabWord){"placate", "make (someone) less angry or hostile.", false};
            all_sets[i].words[3] = (VocabWord){"proclivity", "a tendency to choose or do something regularly", false};
            all_sets[i].words[4] = (VocabWord){"puerile", "childishly silly and immature.", false};
            all_sets[i].words[5] = (VocabWord){"quixotic", "extremely idealistic; unrealistic and impractical.", false};
            all_sets[i].words[6] = (VocabWord){"spendthrift", "a person who spends money in an extravagant,", false};
            all_sets[i].words[7] = (VocabWord){"taciturn", "reserved or uncommunicative in speech;", false};
            all_sets[i].words[8] = (VocabWord){"wary", "feeling or showing caution about possible dangers or problems.", false};
            all_sets[i].words[9] = (VocabWord){"austere", "Strict in manner.", false};
        }else if (i == 3) {
            all_sets[i].words[0] = (VocabWord){"adulterate", "render (something) poorer in quality by adding another substance.", false};
            all_sets[i].words[1] = (VocabWord){"advocate", "a person who publicly supports or recommends a particular cause or policy.", false};
            all_sets[i].words[2] = (VocabWord){"aggrandize", "increase the power, status, or wealth of.", false};
            all_sets[i].words[3] = (VocabWord){"alacrity", "brisk and cheerful readiness.", false};
            all_sets[i].words[4] = (VocabWord){"ambivalent", "having mixed feelings or contradictory ideas about something or someone.", false};
            all_sets[i].words[5] = (VocabWord){"ameliorate", "make (something bad or unsatisfactory) better.", false};
            all_sets[i].words[6] = (VocabWord){"amenable", "open and responsive to suggestion; easily persuaded or controlled.", false};
            all_sets[i].words[7] = (VocabWord){"anachronistic", "belonging to a period other than that being portrayed.", false};
            all_sets[i].words[8] = (VocabWord){"audacious", "showing a willingness to take surprisingly bold risks. ", false};
            all_sets[i].words[9] = (VocabWord){"avaricious", "having or showing an extreme greed for wealth or material gain.", false};
        } else if (i == 4) {
            all_sets[i].words[0] = (VocabWord){"didactic", "mamala", false};
            all_sets[i].words[1] = (VocabWord){"disseminate", "mamala", false};
            all_sets[i].words[2] = (VocabWord){"feasible", "mamala", false};
            all_sets[i].words[3] = (VocabWord){"flout", "mamala", false};
            all_sets[i].words[4] = (VocabWord){"homogeneous", "mamala", false};
            all_sets[i].words[5] = (VocabWord){"humdrum", "mamala", false};
            all_sets[i].words[6] = (VocabWord){"insipid", "mamala", false};
            all_sets[i].words[7] = (VocabWord){"loquacious", "mamala", false};
            all_sets[i].words[8] = (VocabWord){"misanthropic", "mamala ", false};
            all_sets[i].words[9] = (VocabWord){"misnomer", "mamala.", false};
        } else if (i == 5) {
            all_sets[i].words[0] = (VocabWord){"didactic", "mamala", false};
            all_sets[i].words[1] = (VocabWord){"disseminate", "mamala", false};
            all_sets[i].words[2] = (VocabWord){"feasible", "mamala", false};
            all_sets[i].words[3] = (VocabWord){"flout", "mamala", false};
            all_sets[i].words[4] = (VocabWord){"homogeneous", "mamala", false};
            all_sets[i].words[5] = (VocabWord){"humdrum", "mamala", false};
            all_sets[i].words[6] = (VocabWord){"insipid", "mamala", false};
            all_sets[i].words[7] = (VocabWord){"loquacious", "mamala", false};
            all_sets[i].words[8] = (VocabWord){"misanthropic", "mamala ", false};
            all_sets[i].words[9] = (VocabWord){"misnomer", "mamala.", false};
        } else if (i == 6) {
            all_sets[i].words[0] = (VocabWord){"didactic", "mamala", false};
            all_sets[i].words[1] = (VocabWord){"disseminate", "mamala", false};
            all_sets[i].words[2] = (VocabWord){"feasible", "mamala", false};
            all_sets[i].words[3] = (VocabWord){"flout", "mamala", false};
            all_sets[i].words[4] = (VocabWord){"homogeneous", "mamala", false};
            all_sets[i].words[5] = (VocabWord){"humdrum", "mamala", false};
            all_sets[i].words[6] = (VocabWord){"insipid", "mamala", false};
            all_sets[i].words[7] = (VocabWord){"loquacious", "mamala", false};
            all_sets[i].words[8] = (VocabWord){"misanthropic", "mamala ", false};
            all_sets[i].words[9] = (VocabWord){"misnomer", "mamala.", false};
        } else if (i == 7) {
            all_sets[i].words[0] = (VocabWord){"didactic", "mamala", false};
            all_sets[i].words[1] = (VocabWord){"disseminate", "mamala", false};
            all_sets[i].words[2] = (VocabWord){"feasible", "mamala", false};
            all_sets[i].words[3] = (VocabWord){"flout", "mamala", false};
            all_sets[i].words[4] = (VocabWord){"homogeneous", "mamala", false};
            all_sets[i].words[5] = (VocabWord){"humdrum", "mamala", false};
            all_sets[i].words[6] = (VocabWord){"insipid", "mamala", false};
            all_sets[i].words[7] = (VocabWord){"loquacious", "mamala", false};
            all_sets[i].words[8] = (VocabWord){"misanthropic", "mamala ", false};
            all_sets[i].words[9] = (VocabWord){"misnomer", "mamala.", false};
        } else if (i == 8) {
            all_sets[i].words[0] = (VocabWord){"didactic", "mamala", false};
            all_sets[i].words[1] = (VocabWord){"disseminate", "mamala", false};
            all_sets[i].words[2] = (VocabWord){"feasible", "mamala", false};
            all_sets[i].words[3] = (VocabWord){"flout", "mamala", false};
            all_sets[i].words[4] = (VocabWord){"homogeneous", "mamala", false};
            all_sets[i].words[5] = (VocabWord){"humdrum", "mamala", false};
            all_sets[i].words[6] = (VocabWord){"insipid", "mamala", false};
            all_sets[i].words[7] = (VocabWord){"loquacious", "mamala", false};
            all_sets[i].words[8] = (VocabWord){"misanthropic", "mamala ", false};
            all_sets[i].words[9] = (VocabWord){"misnomer", "mamala.", false};
        } else if (i == 9) {
            all_sets[i].words[0] = (VocabWord){"didactic", "mamala", false};
            all_sets[i].words[1] = (VocabWord){"disseminate", "mamala", false};
            all_sets[i].words[2] = (VocabWord){"feasible", "mamala", false};
            all_sets[i].words[3] = (VocabWord){"flout", "mamala", false};
            all_sets[i].words[4] = (VocabWord){"homogeneous", "mamala", false};
            all_sets[i].words[5] = (VocabWord){"humdrum", "mamala", false};
            all_sets[i].words[6] = (VocabWord){"insipid", "mamala", false};
            all_sets[i].words[7] = (VocabWord){"loquacious", "mamala", false};
            all_sets[i].words[8] = (VocabWord){"misanthropic", "mamala ", false};
            all_sets[i].words[9] = (VocabWord){"misnomer", "mamala.", false};
        }
        
    }
}




static uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
    return NUM_SETS;
}

static void menu_draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *context) {
    VocabSet *set = &all_sets[cell_index->row];

    static char name_buffer[32];
    snprintf(name_buffer, sizeof(name_buffer), "%s", set->setName);

    static char progress_buffer[32];
    snprintf(progress_buffer, sizeof(progress_buffer), "%d/%d", set->wordsRead, set->totalWords);

    GFont name_font = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
    GFont progress_font = fonts_get_system_font(FONT_KEY_GOTHIC_18);

    graphics_draw_text(ctx, name_buffer, name_font, 
                       GRect(3, -3, layer_get_bounds(cell_layer).size.w, 28), 
                       GTextOverflowModeTrailingEllipsis, 
                       GTextAlignmentLeft, NULL);

    graphics_draw_text(ctx, progress_buffer, progress_font, 
                       GRect(3, -1, layer_get_bounds(cell_layer).size.w - 6, 24), 
                       GTextOverflowModeTrailingEllipsis, 
                       GTextAlignmentRight, NULL);
}



static void select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
    
    // load_last_word_index(cell_index->row);

    word_window_push(cell_index->row); 
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
    return 0; 
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    s_status_layer = status_bar_layer_create();
    layer_add_child(window_layer, status_bar_layer_get_layer(s_status_layer));

    GEdgeInsets insets = {.top = STATUS_BAR_LAYER_HEIGHT};
    bounds = grect_inset(bounds, insets);

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

    for (int i = 0; i < NUM_SETS; i++) {
        free(all_sets[i].setName);
        free(all_sets[i].words); 
    }
}

void sets_window_push() {
   initialize_sets(); 

    if (!s_main_window) {
        s_main_window = window_create();
        window_set_window_handlers(s_main_window, (WindowHandlers){
            .load = window_load,
            .unload = window_unload
        });
    }
    window_stack_push(s_main_window, true);
}
