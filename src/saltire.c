#include "saltire.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_42_medium_numbers;
static GBitmap *s_res_saltire;
static TextLayer *time_layer;
static BitmapLayer *s_bitmaplayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, true);
  
  s_res_bitham_42_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS);
  s_res_saltire = gbitmap_create_with_resource(RESOURCE_ID_saltire);
  // time_layer
  time_layer = text_layer_create(GRect(0, 104, 144, 43));
  text_layer_set_background_color(time_layer, GColorBlack);
  text_layer_set_text_color(time_layer, GColorWhite);
  text_layer_set_text(time_layer, "00:00");
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  text_layer_set_font(time_layer, s_res_bitham_42_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)time_layer);
  
  // s_bitmaplayer_1
  s_bitmaplayer_1 = bitmap_layer_create(GRect(0, 0, 144, 86));
  bitmap_layer_set_bitmap(s_bitmaplayer_1, s_res_saltire);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(time_layer);
  bitmap_layer_destroy(s_bitmaplayer_1);
  gbitmap_destroy(s_res_saltire);
}
// END AUTO-GENERATED UI CODE

static void handle_tick(struct tm* tick_time, TimeUnits units_changed) {
  static char time_text[] = "00:00";
  strftime(time_text, sizeof(time_text), "%I:%M", tick_time);
  text_layer_set_text(time_layer, time_text);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_saltire(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  time_t now = time(NULL);
  struct tm *current_time = localtime(&now);
  handle_tick(current_time, MINUTE_UNIT);
  tick_timer_service_subscribe(MINUTE_UNIT, handle_tick);

  window_stack_push(s_window, true);
}

void hide_saltire(void) {
  window_stack_remove(s_window, true);
}