// include/order.h
#ifndef ORDER_H
#define ORDER_H

#define MAX_ITEMS 20
#define MAX_NAME 50

typedef struct {
    char name[50];
    double price;
    char size;
    int quantity;
    int is_snack;
} CartItem;

typedef struct {
    char name[MAX_NAME];
    CartItem items[MAX_ITEMS];
    int item_count;
    double total;
    double tax;
} Order;

#endif