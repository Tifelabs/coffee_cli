// include/order.h - Order management functions
#ifndef ORDER_H
#define ORDER_H

#include "types.h"

void update_order_total(Order* order);
void add_to_cart(Order* order, const char* item_name, double price, char size, int quantity);

#endif