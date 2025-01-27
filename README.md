
#### Coffee CLI System

<video controls width="600">
  <source src="./tutor.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>



A terminal-based point of sale system for a coffee shop using ncurses.

## Building

Requirements:
- gcc
- ncurses development library
- make

On Ubuntu/Debian, install dependencies:
```bash
sudo apt-get install build-essential libncurses5-dev
```

Build the project:
```bash
make
```

## Running
```bash
./coffee_shop
```

## Controls
- ↑↓: Select items
- ←→: Select size (for drinks)
- Tab: Switch between drinks and snacks menu
- Enter: Add item to cart
- C: Checkout
- Q: Quit
- N: New order (after checkout)