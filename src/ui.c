#include <ncurses.h>
#include <time.h>
#include "../include/ui.h"
#include "../include/types.h"

void draw_border(WINDOW* win) {
    wattron(win, COLOR_PAIR(1));
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(1));
}

void draw_menu(WINDOW* win, int selected, int start_y) {
    int width;
    getmaxyx(win, width, width); // Only get width if height is not needed

    // Draw header
    wattron(win, COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win, 1, width/2 - 10, "COFFEE MENU");
    wattroff(win, COLOR_PAIR(3) | A_BOLD);

    // Draw menu items
    for (int i = 0; i < MENU_SIZE; i++) {
        // Highlight selected item
        if (i == selected) {
            wattron(win, COLOR_PAIR(2) | A_BOLD);
        }

        // Display menu item with price
        mvwprintw(win, start_y + i, 2, "%d. %-20s $%.2f", 
                  i + 1, MENU_ITEMS[i], PRICES[i]);

        if (i == selected) {
            wattroff(win, COLOR_PAIR(2) | A_BOLD);
        }
    }
}

void draw_size_selector(WINDOW* win, int selected_size, int y) {
    // Size label
    mvwprintw(win, y, 2, "Size: ");
    const char* sizes[] = {"Small", "Medium", "Large"};

    // Draw size options
    for (int i = 0; i < 3; i++) {
        if (i == selected_size) {
            wattron(win, COLOR_PAIR(2) | A_BOLD);
        }

        mvwprintw(win, y, 15 + i*15, "[%s]", sizes[i]);

        if (i == selected_size) {
            wattroff(win, COLOR_PAIR(2) | A_BOLD);
        }
    }
}

void draw_cart(WINDOW* win, Order* order, int start_y) {
    int height;
    getmaxyx(win, height, height); // Only get height if width is not needed

    // Cart header
    wattron(win, COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win, start_y, 2, "Shopping Cart - %s", order->name);
    wattroff(win, COLOR_PAIR(3) | A_BOLD);

    // Column headers
    mvwprintw(win, start_y + 1, 2, "%-20s %-6s %-6s %-8s", 
              "Item", "Size", "Qty", "Price");

    // Cart items
    for (int i = 0; i < order->item_count; i++) {
        CartItem* item = &order->items[i];
        mvwprintw(win, start_y + 2 + i, 2, "%-20s %-6c %-6d $%-7.2f",
                  item->name, item->size, item->quantity,
                  item->price * item->quantity);
    }

    // Total amount
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, start_y + height - 4, 2, "Total: $%.2f", order->total);
    wattroff(win, COLOR_PAIR(3));
}

void draw_receipt(WINDOW* win, Order* order) {
    int width, height;
    getmaxyx(win, height, width);

    // Get current time
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    char time_str[26];
    strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    // Receipt header
    wattron(win, COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win, 1, width/2 - 15, "COFFEE SHOP RECEIPT");
    wattroff(win, COLOR_PAIR(3) | A_BOLD);

    // Receipt details
    mvwprintw(win, 3, 2, "Date: %s", time_str);
    mvwprintw(win, 4, 2, "Customer: %s", order->name);

    // Column headers
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 6, 2, "%-20s %-6s %-6s %-8s", 
              "Item", "Size", "Qty", "Price");
    wattroff(win, COLOR_PAIR(2));

    // Receipt items
    for (int i = 0; i < order->item_count; i++) {
        CartItem* item = &order->items[i];
        mvwprintw(win, 7 + i, 2, "%-20s %-6c %-6d $%-7.2f",
                  item->name, item->size, item->quantity,
                  item->price * item->quantity);
    }

    // Total and footer
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, height - 4, 2, "Total Amount: $%.2f", order->total);
    wattroff(win, COLOR_PAIR(3));

    wattron(win, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(win, height - 3, 2, "Thank you for your order!");
    wattroff(win, COLOR_PAIR(2) | A_BOLD);
}

void draw_loading_animation(WINDOW* win) {
    int width, height;
    getmaxyx(win, height, width);

    const char* frames[] = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
    const int frame_count = 10;

    for (int i = 0; i < frame_count; i++) {
        mvwprintw(win, height/2, width/2 - 10, "Loading %s", frames[i]);
        wrefresh(win);
        napms(100);
    }
}

void draw_error_message(WINDOW* win, const char* message) {
    int height;
    getmaxyx(win, height, height); // Only get height if width is not needed

    wattron(win, COLOR_PAIR(4) | A_BOLD);  // Assuming COLOR_PAIR(4) is defined for errors
    mvwprintw(win, height - 1, 2, "Error: %s", message);
    wattroff(win, COLOR_PAIR(4) | A_BOLD);
    wrefresh(win);
    napms(2000);  // Show error for 2 seconds
}