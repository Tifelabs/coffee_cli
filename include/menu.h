#ifndef MENU_H
#define MENU_H

#define MENU_SIZE 6
#define SNACK_SIZE 5  // Rename macro to avoid conflicts with variable names

// Declare arrays and constants
extern const char* MENU_ITEMS[];
extern const char* SNACK_ITEMS[];
extern const double PRICES[];
extern const double SNACK_PRICES[];
extern const char* MENU_DESCRIPTIONS[];
extern const char* SNACK_DESCRIPTIONS[];
extern const int DRINK_CALORIES[];
extern const int SNACK_CALORIES[];
extern const double SIZE_MULTIPLIERS[];
extern const double CALORIE_MULTIPLIERS[];
extern const double TAX_RATE;

// Declare functions
int get_menu_size(int is_snacks);
const char* get_item_name(int index, int is_snacks);
double get_item_price(int index, int is_snacks);
const char* get_item_description(int index, int is_snacks);
int get_item_calories(int index, int is_snacks, char size);
double get_size_multiplier(char size);
int is_item_available(int index, int is_snacks);
const char* get_drink_category(int index);
double calculate_final_price(int index, int is_snacks, char size);

#endif // MENU_H
