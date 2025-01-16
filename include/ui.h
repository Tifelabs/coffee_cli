// include/ui.h - User interface functions
#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include "types.h"

void draw_border(WINDOW* win);
void draw_menu(WINDOW* win, int selected, int start_y);
void draw_size_selector(WINDOW* win, int selected_size, int y);
void draw_cart(WINDOW* win, Order* order, int start_y);
void draw_receipt(WINDOW* win, Order* order);

#endif