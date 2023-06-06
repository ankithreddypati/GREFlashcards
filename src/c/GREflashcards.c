#include <pebble.h>
#include "windows/sets.h"
#include "src/windows/about.h"
//#include "windows/quiz.h"

#define NUM_WINDOWS 3
#define SET_PROGRESS_KEY 100 

static Window *s_main_window;
static MenuLayer *s_menu_layer;
static StatusBarLayer *s_status_layer;



static uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context)
{
  return NUM_WINDOWS;
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data)
{
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *data)
{
  menu_cell_basic_header_draw(ctx, cell_layer, "GRE flashcards");
}

static void draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *context)
{
  switch (cell_index->row)
  {
  case 0:
    menu_cell_basic_draw(ctx, cell_layer, "Flashcards", "continue with study.", NULL);
    break;
  case 1:
    menu_cell_basic_draw(ctx, cell_layer, "Quizes", "test yourself.", NULL);
    break;
  case 2:
    menu_cell_basic_draw(ctx, cell_layer, "About", NULL, NULL);
    break;
  default:
    break;
  }
}


static void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context)
{
  switch (cell_index->row)
  {
  case 0:

    sets_window_push();
    break;
  case 1:
    //quizes_window_push();
    break;
  case 2:
    about_window_push();
    break;
  default:
    break;
  }
}



static void window_load(Window *window)
{
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  const GEdgeInsets status_insets = {.top = STATUS_BAR_LAYER_HEIGHT};
  bounds = grect_inset(bounds, status_insets);

  s_status_layer = status_bar_layer_create();
  status_bar_layer_set_colors(s_status_layer, GColorWhite, GColorBlack);

  s_menu_layer = menu_layer_create(bounds);
  menu_layer_set_click_config_onto_window(s_menu_layer, window);
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks){
      .get_num_rows = get_num_rows_callback,
      .draw_row = draw_row_callback,
      .get_header_height = PBL_IF_RECT_ELSE(menu_get_header_height_callback, NULL),
      .draw_header = PBL_IF_RECT_ELSE(menu_draw_header_callback, NULL),
      .select_click = select_callback,
  });
  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
  layer_add_child(window_layer, status_bar_layer_get_layer(s_status_layer));
}

static void window_unload(Window *window)
{
  menu_layer_destroy(s_menu_layer);
  status_bar_layer_destroy(s_status_layer);
}

static void init()
{
  
  s_main_window = window_create();
  
  window_set_window_handlers(s_main_window, (WindowHandlers){
      .load = window_load,
      .unload = window_unload,
  });
  window_stack_push(s_main_window, true);
  //load_set_progress();
}

static void deinit()
{
  window_destroy(s_main_window);
}

int main()
{
  init();
  app_event_loop();
  deinit();
}

 // functions for persitant data
// static void load_set_progress() {
//     for (int i = 0; i < NUM_SETS; i++) {
//         int key = SET_PROGRESS_KEY + i;
//         if (persist_exists(key)) {
//             persist_read_data(key, &all_sets[i], sizeof(VocabSet));
//         }
//     }
// }
