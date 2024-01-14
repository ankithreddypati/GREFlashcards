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
            all_sets[i].words[0] = (VocabWord){"banal", "so lacking in originality as to be obvious and boring.", false};
            all_sets[i].words[1] = (VocabWord){"benign", "gentle and kind.", false};
            all_sets[i].words[2] = (VocabWord){"brazen", "bold and without shame.", false};
            all_sets[i].words[3] = (VocabWord){"calumny", "the making of false and defamatory statements about someone", false};
            all_sets[i].words[4] = (VocabWord){"castigate", "reprimand (someone) severely.", false};
            all_sets[i].words[5] = (VocabWord){"candid", "truthful and straightforward; frank.", false};
            all_sets[i].words[6] = (VocabWord){"caustic", "sarcastic in a scathing and bitter way.", false};
            all_sets[i].words[7] = (VocabWord){"construe", "interpret (a word or action) in a particular way.", false};
            all_sets[i].words[8] = (VocabWord){"contrite", "feeling or expressing remorse at the recognition ", false};
            all_sets[i].words[9] = (VocabWord){"convoluted", "extremely complex and difficult to follow..", false};
        } else if (i == 5) {
            all_sets[i].words[0] = (VocabWord){"covet", "yearn to possess (something, especially something belonging to another)", false};
            all_sets[i].words[1] = (VocabWord){"craven", "contemptibly lacking in courage; cowardly.", false};
            all_sets[i].words[2] = (VocabWord){"decorum", "behaviour in keeping with good taste and propriety.", false};
            all_sets[i].words[3] = (VocabWord){"deft", "neatly skilful and quick in one's movements.", false};
            all_sets[i].words[4] = (VocabWord){"demur", "raise objections or show reluctance.", false};
            all_sets[i].words[5] = (VocabWord){"derivative", "something which is based on another source.", false};
            all_sets[i].words[6] = (VocabWord){"desiccate", "remove the moisture from (something); cause to become completely dry.", false};
            all_sets[i].words[7] = (VocabWord){"diatribe", "a forceful and bitter verbal attack against someone or something.", false};
            all_sets[i].words[8] = (VocabWord){"incredulous", "unwilling or unable to believe something. ", false};
            all_sets[i].words[9] = (VocabWord){"ingenuous", "innocent and unsuspecting.", false};
        } else if (i == 6) {
            all_sets[i].words[0] = (VocabWord){"betray", "unintentionally reveal; be evidence of.", false};
            all_sets[i].words[1] = (VocabWord){"bucolic", "relating to the pleasant aspects of the countryside and country life.", false};
            all_sets[i].words[2] = (VocabWord){"burgeon", "begin to grow or increase rapidly; flourish.", false};
            all_sets[i].words[3] = (VocabWord){"cacophonous", "involving or producing a harsh, discordant mixture of sounds.", false};
            all_sets[i].words[4] = (VocabWord){"canonize", "place in or regard as belonging to a canon of literary or artistic works", false};
            all_sets[i].words[5] = (VocabWord){"censure", "express severe disapproval of (someone or something),", false};
            all_sets[i].words[6] = (VocabWord){"chicanery", "the use of deception or subterfuge to achieve one's purpose.", false};
            all_sets[i].words[7] = (VocabWord){"coalesce", "come together to form one mass or whole.", false};
            all_sets[i].words[8] = (VocabWord){"cogent", "(of an argument or case) clear, logical, and convincing. ", false};
            all_sets[i].words[9] = (VocabWord){"compelling", "evoking interest, attention, or admiration in a powerfully irresistible way..", false};
        } else if (i == 7) {
            all_sets[i].words[0] = (VocabWord){"abate", "(of something unpleasant or severe) become less intense or widespread.", false};
            all_sets[i].words[1] = (VocabWord){"abjure", "solemnly renounce (a belief, cause, or claim).", false};
            all_sets[i].words[2] = (VocabWord){"anomalous", "deviating from what is standard, normal, or expected.", false};
            all_sets[i].words[3] = (VocabWord){"antipathy", "a deep-seated feeling of aversion.", false};
            all_sets[i].words[4] = (VocabWord){"arcane", "understood by few; mysterious or secret.", false};
            all_sets[i].words[5] = (VocabWord){"arduous", "involving or requiring strenuous effort; difficult and tiring.", false};
            all_sets[i].words[6] = (VocabWord){"artless", "without effort or pretentiousness; natural and simple.", false};
            all_sets[i].words[7] = (VocabWord){"ascetic", "characterized by severe self-discipline and abstention", false};
            all_sets[i].words[8] = (VocabWord){"assuage", "make (an unpleasant feeling) less intense. ", false};
            all_sets[i].words[9] = (VocabWord){"contend", "compete with others in a struggle to achieve (something)..", false};
        } else if (i == 8) {
            all_sets[i].words[0] = (VocabWord){"copious", "abundant in supply or quantity.", false};
            all_sets[i].words[1] = (VocabWord){"cosmopolitan", "including people from many different countries.", false};
            all_sets[i].words[2] = (VocabWord){"deference", "polite submission and respect.", false};
            all_sets[i].words[3] = (VocabWord){"desultory", "lacking a plan, purpose, or enthusiasm.", false};
            all_sets[i].words[4] = (VocabWord){"diffident", "modest or shy because of a lack of self-confidence.", false};
            all_sets[i].words[5] = (VocabWord){"dilatory", "1. slow to act. 2. intended to cause delay.", false};
            all_sets[i].words[6] = (VocabWord){"equivocate", "use ambiguous language so as to conceal the truth or avoid committing oneself.", false};
            all_sets[i].words[7] = (VocabWord){"polarize", "divide or cause to divide into two sharply contrasting groups or sets of opinions or beliefs.", false};
            all_sets[i].words[8] = (VocabWord){"prodigal", "having or giving something on a lavish scale. ", false};
            all_sets[i].words[9] = (VocabWord){"verbose", "using or expressed in more words than are needed.", false};
        } else if (i == 9) {
            all_sets[i].words[0] = (VocabWord){"abhor", "regard with disgust and hatred.", false};
            all_sets[i].words[1] = (VocabWord){"boisterous", "noisy, energetic, and cheerful.", false};
            all_sets[i].words[2] = (VocabWord){"chivalrous", "(of a man or his behaviour) courteous and gallant,", false};
            all_sets[i].words[3] = (VocabWord){"churlish", "rude in a mean-spirited and surly way.", false};
            all_sets[i].words[4] = (VocabWord){"clandestine", "kept secret or done secretively, especially because illicit.", false};
            all_sets[i].words[5] = (VocabWord){"complacent", "showing smug or uncritical satisfaction with oneself or one's achievements.", false};
            all_sets[i].words[6] = (VocabWord){"cumbersome", "large or heavy and therefore difficult to carry or use; unwieldy.", false};
            all_sets[i].words[7] = (VocabWord){"debilitating", "make (someone) very weak and infirm.", false};
            all_sets[i].words[8] = (VocabWord){"deliberate", "done consciously and intentionally. ", false};
            all_sets[i].words[9] = (VocabWord){"droll", "curious or unusual in a way that provokes dry amusement.", false};
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
