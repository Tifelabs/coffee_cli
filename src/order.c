// src/order.c - Order management implementation
#include <string.h>
#include "../include/order.h"
#include "../include/types.h"

void update_order_total(Order* order) {
    order->total = 0;
    for (int i = 0; i < order->item_count; i++) {
        order->total += order->items[i].price * order->items[i].quantity;
    }
}

void add_to_cart(Order* order, const char* item_name, double price, char size, int quantity) {
    if (order->item_count < MAX_ITEMS) {
        CartItem* item = &order->items[order->item_count];
        strncpy(item->name, item_name, 49);
        item->size = size;
        item->quantity = quantity;
        
        double multiplier = 1.0;
        if (size == 'M') multiplier = 1.2;
        if (size == 'L') multiplier = 1.4;
        item->price = price * multiplier;
        
        order->item_count++;
        update_order_total(order);
    }
}
