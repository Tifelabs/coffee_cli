// include/types.h - Data structures and constants
#ifndef TYPES_H
#define TYPES_H

#define MAX_ITEMS 10
#define MAX_NAME 50
#define MENU_SIZE 6

typedef struct {
    char name[50];
    double price;
    char size;  // 'S', 'M', 'L'
    int quantity;
} CartItem;

typedef struct {
    char name[MAX_NAME];
    CartItem items[MAX_ITEMS];
    int item_count;
    double total;
} Order;

// Menu data
extern const char* MENU_ITEMS[];
extern const double PRICES[];
extern const double SIZE_MULTIPLIERS[];

#endif