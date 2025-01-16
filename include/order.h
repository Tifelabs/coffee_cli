#ifndef ORDER_H
#define ORDER_H

#include "cart.h"

typedef struct {
    CartItem* items;
    int count;
    double total;
    char* timestamp;
} Order;

Order* create_order(Cart* cart);
void print_order(Order* order);
void free_order(Order* order);

#endif /* ORDER_H */