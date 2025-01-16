#include "menu.h"
#include <stddef.h>  /* For NULL */
#include <stdio.h>
#include "cart.h"
#include "ui.h"
#include "order.h"


/* Constants for array sizes */
#define MENU_SIZE 6
#define SNACK_SIZE 5

/* Menu items and their details */
const char* MENU_ITEMS[] = {
    "Espresso",
    "Cappuccino",
    "Latte",
    "Mocha",
    "Americano",
    "Cold Brew"
};

const char* SNACK_ITEMS[] = {
    "Apple Pie",
    "Brown Cookie",
    "Cinnamon Roll",
    "Donut",
    "Sausage"
};

/* Example Descriptions */
const char* MENU_DESCRIPTIONS[] = {
    "A strong black coffee.",
    "A creamy coffee with frothy milk.",
    "A smooth coffee with steamed milk.",
    "A rich coffee with chocolate syrup.",
    "A simple coffee with hot water.",
    "A refreshing cold coffee."
};

const char* SNACK_DESCRIPTIONS[] = {
    "A delicious slice of apple pie.",
    "A chewy and sweet cookie.",
    "A warm and spiced cinnamon roll.",
    "A classic glazed donut.",
    "A savory sausage roll."
};

/* Example Calorie Information */
const int DRINK_CALORIES[] = {5, 150, 180, 200, 10, 15};
const int SNACK_CALORIES[] = {320, 150, 400, 250, 350};

/* Multipliers */
const double CALORIE_MULTIPLIERS[] = {1.0, 1.5, 2.0};
const double SIZE_MULTIPLIERS[] = {1.0, 1.2, 1.5};

/* Prices for each menu item */
const double PRICES[] = {2.99, 3.99, 3.99, 4.29, 3.49, 3.99};
const double SNACK_PRICES[] = {3.99, 2.49, 3.99, 1.99, 4.49};

/* Tax Rate */
const double TAX_RATE = 0.07;

/* Function implementations */
double get_size_multiplier(char size) {
    switch (size) {
        case 'S': return SIZE_MULTIPLIERS[0];
        case 'M': return SIZE_MULTIPLIERS[1];
        case 'L': return SIZE_MULTIPLIERS[2];
        default: return 1.0;  /* Default to small if size is invalid */
    }
}

int get_menu_size(int is_snacks) {
    return is_snacks ? SNACK_SIZE : MENU_SIZE;
}

const char* get_item_name(int index, int is_snacks) {
    if (is_snacks) {
        return (index >= 0 && index < SNACK_SIZE) ? SNACK_ITEMS[index] : NULL;
    } else {
        return (index >= 0 && index < MENU_SIZE) ? MENU_ITEMS[index] : NULL;
    }
}

double get_item_price(int index, int is_snacks) {
    if (is_snacks) {
        return (index >= 0 && index < SNACK_SIZE) ? SNACK_PRICES[index] : 0.0;
    } else {
        return (index >= 0 && index < MENU_SIZE) ? PRICES[index] : 0.0;
    }
}

const char* get_item_description(int index, int is_snacks) {
    if (is_snacks) {
        return (index >= 0 && index < SNACK_SIZE) ? SNACK_DESCRIPTIONS[index] : NULL;
    } else {
        return (index >= 0 && index < MENU_SIZE) ? MENU_DESCRIPTIONS[index] : NULL;
    }
}

int get_item_calories(int index, int is_snacks, char size) {
    int base_calories;
    
    if (is_snacks) {
        if (index < 0 || index >= SNACK_SIZE) return 0;
        return SNACK_CALORIES[index];
    } else {
        if (index < 0 || index >= MENU_SIZE) return 0;
        base_calories = DRINK_CALORIES[index];
        switch (size) {
            case 'S': return base_calories;
            case 'M': return (int)(base_calories * CALORIE_MULTIPLIERS[1]);
            case 'L': return (int)(base_calories * CALORIE_MULTIPLIERS[2]);
            default: return base_calories;
        }
    }
}

int is_item_available(int index, int is_snacks) {
    return is_snacks ? (index >= 0 && index < SNACK_SIZE) : (index >= 0 && index < MENU_SIZE);
}

const char* get_drink_category(int index) {
    if (index < 0 || index >= MENU_SIZE) return NULL;
    return (index == 5) ? "Cold" : "Hot";
}

double calculate_final_price(int index, int is_snacks, char size) {
    double base_price = get_item_price(index, is_snacks);
    if (!is_snacks) {
        base_price *= get_size_multiplier(size);
    }
    return base_price * (1 + TAX_RATE);
}

int main() {

    Cart* cart = create_cart();
    init_ui();
    
    /* Main program loop */
    display_menu();
    
    /* Add your menu interaction logic here */
    
    /* Cleanup */
    free_cart(cart);
    cleanup_ui();

    printf("Menu size: %d\n", get_menu_size(0));    /* Test function */
    printf("Snack size: %d\n", get_menu_size(1));   /* Test function */
    return 0;




}