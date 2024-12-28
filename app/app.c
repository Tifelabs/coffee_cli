#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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

// Menu items with prices
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

void draw_border(WINDOW* win) {
    wattron(win, COLOR_PAIR(1));
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(1));
}

void draw_menu(WINDOW* win, int selected, int start_y) {
    int width, height;
    getmaxyx(win, height, width);
    
    mvwprintw(win, 1, width/2 - 10, "COFFEE MENU");
    
    for (int i = 0; i < MENU_SIZE; i++) {
        if (i == selected)
            wattron(win, COLOR_PAIR(2) | A_BOLD);
            
        mvwprintw(win, start_y + i, 2, "%d. %-20s $%.2f", 
                  i + 1, MENU_ITEMS[i], PRICES[i]);
                  
        if (i == selected)
            wattroff(win, COLOR_PAIR(2) | A_BOLD);
    }
}

void draw_size_selector(WINDOW* win, int selected_size, int y) {
    mvwprintw(win, y, 2, "Size: ");
    const char* sizes[] = {"Small", "Medium", "Large"};
    
    for (int i = 0; i < 3; i++) {
        if (i == selected_size)
            wattron(win, COLOR_PAIR(2) | A_BOLD);
            
        mvwprintw(win, y, 15 + i*15, "[%s]", sizes[i]);
        
        if (i == selected_size)
            wattroff(win, COLOR_PAIR(2) | A_BOLD);
    }
}

void draw_cart(WINDOW* win, Order* order, int start_y) {
    int width, height;
    getmaxyx(win, height, width);
    
    mvwprintw(win, start_y, 2, "Shopping Cart - %s", order->name);
    mvwprintw(win, start_y + 1, 2, "%-20s %-6s %-6s %-8s", 
              "Item", "Size", "Qty", "Price");
              
    for (int i = 0; i < order->item_count; i++) {
        CartItem* item = &order->items[i];
        mvwprintw(win, start_y + 2 + i, 2, "%-20s %-6c %-6d $%-7.2f",
                  item->name, item->size, item->quantity,
                  item->price * item->quantity);
    }
    
    mvwprintw(win, start_y + height - 4, 2, "Total: $%.2f", order->total);
}

void update_order_total(Order* order) {
    order->total = 0;
    for (int i = 0; i < order->item_count; i++) {
        order->total += order->items[i].price * order->items[i].quantity;
    }
}

void add_to_cart(Order* order, const char* item_name, double price, 
                 char size, int quantity) {
    if (order->item_count < MAX_ITEMS) {
        CartItem* item = &order->items[order->item_count];
        strncpy(item->name, item_name, 49);
        item->size = size;
        item->quantity = quantity;
        
        // Adjust price based on size
        double multiplier = 1.0;
        if (size == 'M') multiplier = 1.2;
        if (size == 'L') multiplier = 1.4;
        item->price = price * multiplier;
        
        order->item_count++;
        update_order_total(order);
    }
}

void draw_receipt(WINDOW* win, Order* order) {
    int width, height;
    getmaxyx(win, height, width);
    
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    char time_str[26];
    strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    
    mvwprintw(win, 1, width/2 - 15, "COFFEE SHOP RECEIPT");
    mvwprintw(win, 3, 2, "Date: %s", time_str);
    mvwprintw(win, 4, 2, "Customer: %s", order->name);
    mvwprintw(win, 6, 2, "%-20s %-6s %-6s %-8s", 
              "Item", "Size", "Qty", "Price");
              
    for (int i = 0; i < order->item_count; i++) {
        CartItem* item = &order->items[i];
        mvwprintw(win, 7 + i, 2, "%-20s %-6c %-6d $%-7.2f",
                  item->name, item->size, item->quantity,
                  item->price * item->quantity);
    }
    
    mvwprintw(win, height - 4, 2, "Total Amount: $%.2f", order->total);
    mvwprintw(win, height - 3, 2, "Thank you for your order!");
}

int main() {
    // Initialize ncurses
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(1);
    keypad(stdscr, TRUE);
    
    // Color pairs
    init_pair(1, COLOR_CYAN, COLOR_BLACK);    // borders
    init_pair(2, COLOR_GREEN, COLOR_BLACK);   // selection
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);  // highlights
    
    // Get terminal size
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Create main window
    WINDOW* win = newwin(max_y, max_x, 0, 0);
    
    // Initialize order
    Order order = {0};
    strcpy(order.name, "Guest");
    
    int selected_item = 0;
    int selected_size = 0;  // 0=S, 1=M, 2=L
    int state = 0;  // 0=name, 1=menu, 2=receipt
    char input_buffer[MAX_NAME] = {0};
    int input_pos = 0;
    
    while (1) {
        werase(win);
        draw_border(win);
        
        switch (state) {
            case 0:  // Name input
                mvwprintw(win, max_y/2 - 1, max_x/2 - 15, 
                         "Welcome to Coffee Terminal!");
                mvwprintw(win, max_y/2, max_x/2 - 15, 
                         "Enter your name: %s", input_buffer);
                wrefresh(win);
                
                int ch = getch();
                if (ch == '\n' && input_pos > 0) {
                    strncpy(order.name, input_buffer, MAX_NAME-1);
                    state = 1;
                } else if (ch == KEY_BACKSPACE || ch == 127) {
                    if (input_pos > 0) input_buffer[--input_pos] = 0;
                } else if (input_pos < MAX_NAME-1 && ch >= 32 && ch <= 126) {
                    input_buffer[input_pos++] = ch;
                    input_buffer[input_pos] = 0;
                }
                break;
                
            case 1:  // Menu and cart
                draw_menu(win, selected_item, 3);
                draw_size_selector(win, selected_size, 10);
                draw_cart(win, &order, 13);
                
                mvwprintw(win, max_y-2, 2, 
                         "↑↓: Select item | ←→: Select size | Enter: Add to cart | C: Checkout | Q: Quit");
                         
                wrefresh(win);
                
                ch = getch();
                switch (ch) {
                    case KEY_UP:
                        selected_item = (selected_item - 1 + MENU_SIZE) % MENU_SIZE;
                        break;
                    case KEY_DOWN:
                        selected_item = (selected_item + 1) % MENU_SIZE;
                        break;
                    case KEY_LEFT:
                        selected_size = (selected_size - 1 + 3) % 3;
                        break;
                    case KEY_RIGHT:
                        selected_size = (selected_size + 1) % 3;
                        break;
                    case '\n':
                        add_to_cart(&order, MENU_ITEMS[selected_item],
                                  PRICES[selected_item],
                                  "SML"[selected_size], 1);
                        break;
                    case 'c':
                    case 'C':
                        if (order.item_count > 0) state = 2;
                        break;
                    case 'q':
                    case 'Q':
                        goto cleanup;
                }
                break;
                
            case 2:  // Receipt
                draw_receipt(win, &order);
                mvwprintw(win, max_y-2, 2, 
                         "Press Q to quit or N for new order");
                wrefresh(win);
                
                ch = getch();
                if (ch == 'q' || ch == 'Q') {
                    goto cleanup;
                } else if (ch == 'n' || ch == 'N') {
                    memset(&order, 0, sizeof(Order));
                    strcpy(order.name, "Guest");
                    state = 0;
                    input_pos = 0;
                    memset(input_buffer, 0, MAX_NAME);
                }
                break;
        }
        
        napms(50);  // Small delay for real-time updates
    }
    
cleanup:
    delwin(win);
    endwin();
    return 0;
}