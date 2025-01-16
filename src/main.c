// src/main.c - Main program
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../include/types.h"
#include "../include/ui.h"
#include "../include/order.h"


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
                         "MAKE COFFEE GREAT AGAIN..!");
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