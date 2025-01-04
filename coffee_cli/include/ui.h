// include/ui.h
#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include "order.h"

void draw_border(WINDOW* win);
void draw_menu(WINDOW* win, int selected, int start_y, int show_snacks);
void draw_size_selector(WINDOW* win, int selected_size, int y, int show_snacks);
void draw_cart(WINDOW* win, Order* order, int start_y);
void draw_receipt(WINDOW* win, Order* order);

#endif