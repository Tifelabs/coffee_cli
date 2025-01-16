#ifndef CART_H
#define CART_H

typedef struct {
    int item_index;
    int is_snack;
    char size;
    int quantity;
} CartItem;

typedef struct {
    CartItem* items;
    int count;
    int capacity;
} Cart;

Cart* create_cart(void);
void add_to_cart(Cart* cart, int item_index, int is_snack, char size, int quantity);
void clear_cart(Cart* cart);
double get_cart_total(Cart* cart);
void free_cart(Cart* cart);

#endif /* CART_H */