#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include "cart.h"

void init_ui(void);
void display_menu(void);
void display_cart(Cart* cart);
void display_order_confirmation(Order* order);
void cleanup_ui(void);

#endif /* UI_H */