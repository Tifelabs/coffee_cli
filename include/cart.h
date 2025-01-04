// include/cart.h
#ifndef CART_H
#define CART_H

#include "order.h"

void add_to_cart(Order* order, const char* item_name, double price, 
                 char size, int quantity, int is_snack);
void update_order_total(Order* order);

#endif




