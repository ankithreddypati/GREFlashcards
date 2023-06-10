#include "about.h"

static Window *s_main_window;
static TextLayer *s_header_layer, *s_text_layer;
static Layer *s_background_layer;

static Animation *s_appear_anim = NULL;

static void click_handler(ClickRecognizerRef recognizer, void *context)
{
    window_stack_pop(true);
}

static void anim_stopped_handler(Animation *animation, bool finished, void *context)
{
    s_appear_anim = NULL;
}

static void background_update_proc(Layer *layer, GContext *ctx)
{
    graphics_context_set_fill_color(ctx, PBL_IF_COLOR_ELSE(GColorLightGray, GColorWhite));
    graphics_fill_rect(ctx, layer_get_bounds(layer), 0, 0);
}

static void click_config_provider(void *context)
{
    window_single_click_subscribe(BUTTON_ID_UP, click_handler);
    window_single_click_subscribe(BUTTON_ID_SELECT, click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, click_handler);
}

static void window_load(Window *window)
{
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    window_set_click_config_provider(window, click_config_provider);

    const GEdgeInsets background_insets = {.top = bounds.size.h};
    s_background_layer = layer_create(grect_inset(bounds, background_insets));
    layer_set_update_proc(s_background_layer, background_update_proc);
    layer_add_child(window_layer, s_background_layer);

    s_header_layer = text_layer_create(GRect(ABOUT_WINDOW_MARGIN, bounds.size.h + ABOUT_WINDOW_MARGIN, bounds.size.w - (2 * ABOUT_WINDOW_MARGIN), bounds.size.h));
    text_layer_set_text(s_header_layer, "About");
    text_layer_set_background_color(s_header_layer, GColorClear);
    text_layer_set_text_alignment(s_header_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft));
    text_layer_set_font(s_header_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    layer_add_child(window_layer, text_layer_get_layer(s_header_layer));

    s_text_layer = text_layer_create(GRect(ABOUT_WINDOW_MARGIN + ABOUT_HEADER_OFFSET, bounds.size.h + ABOUT_WINDOW_MARGIN, bounds.size.w - (2 * ABOUT_WINDOW_MARGIN), bounds.size.h));
    text_layer_set_text(s_text_layer, "study flashcards: Contains most repeated GRE vocabulary words in sets..\n\nMove to next word or set with up/down buttonss and use center button to see the meaning of words.");
    text_layer_set_background_color(s_text_layer, GColorClear);
    text_layer_set_text_alignment(s_text_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft));
    text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

static void window_unload(Window *window)
{
    layer_destroy(s_background_layer);
    text_layer_destroy(s_text_layer);

    window_destroy(window);
    s_main_window = NULL;
}

static void window_appear(Window *window)
{
    if (s_appear_anim)
    {
        // In progress, cancel
        animation_unschedule(s_appear_anim);
    }

    GRect bounds = layer_get_bounds(window_get_root_layer(window));

    Layer *text_layer = text_layer_get_layer(s_text_layer);
    Layer *header_layer = text_layer_get_layer(s_header_layer);

    GRect start = layer_get_frame(s_background_layer);
    GRect finish = bounds;
    Animation *background_anim = (Animation *)property_animation_create_layer_frame(s_background_layer, &start, &finish);

    start = layer_get_frame(header_layer);
    const GEdgeInsets header_insets = {
        .top = PBL_IF_ROUND_ELSE(ABOUT_ROUND_OFFSET, 0),
        .right = ABOUT_WINDOW_MARGIN,
        .left = ABOUT_WINDOW_MARGIN};
    finish = grect_inset(bounds, header_insets);
    Animation *header_anim = (Animation *)property_animation_create_layer_frame(header_layer, &start, &finish);

    start = layer_get_frame(text_layer);
    const GEdgeInsets text_insets = {
        .top = PBL_IF_ROUND_ELSE(ABOUT_ROUND_OFFSET + ABOUT_HEADER_OFFSET, ABOUT_HEADER_OFFSET),
        .right = PBL_IF_ROUND_ELSE(ABOUT_WINDOW_MARGIN, ABOUT_WINDOW_MARGIN),
        .left = PBL_IF_ROUND_ELSE(ABOUT_WINDOW_MARGIN, ABOUT_WINDOW_MARGIN)};
    finish = grect_inset(bounds, text_insets);
    Animation *text_anim = (Animation *)property_animation_create_layer_frame(text_layer, &start, &finish);

    s_appear_anim = animation_spawn_create(background_anim, header_anim, text_anim, NULL);
    animation_set_handlers(s_appear_anim, (AnimationHandlers){.stopped = anim_stopped_handler}, NULL);
    animation_set_delay(s_appear_anim, 50);
    animation_schedule(s_appear_anim);
}

void about_window_push()
{
    if (!s_main_window)
    {
        s_main_window = window_create();
        window_set_background_color(s_main_window, GColorBlack);
        window_set_window_handlers(s_main_window, (WindowHandlers){
            .load = window_load,
            .unload = window_unload,
            .appear = window_appear
        });
    }
    window_stack_push(s_main_window, true);
}
