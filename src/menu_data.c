// src/menu_data.c - Menu items and prices
#include "../include/types.h"

const char* MENU_ITEMS[] = {
    "Espresso",
    "Cappuccino",
    "Latte",
    "Mocha",
    "Americano",
    "Cold Brew"
};

const double PRICES[] = {2.99, 3.99, 3.99, 4.29, 3.49, 3.99};
const double SIZE_MULTIPLIERS[] = {1.0, 1.2, 1.4};  // S, M, L
