#Coffee ascii# Define ASCII art for coffee cups
small_cup = """
    ( (
     ) )
  ........
  |      |]
  \      / 
   `----'
"""

medium_cup = """
     ( (
      ) )
   ..........
   |        |]
   |        |
   \        / 
    `------'
"""

large_cup = """
       ( (
        ) )
     ............
     |          |]
     |          |
     |          |
     \          / 
      `--------'
"""

# Store the cups in a Python list
coffee_cups = [small_cup, medium_cup, large_cup]

# Print each coffee cup with its size
sizes = ["Small", "Medium", "Large"]
for size, cup in zip(sizes, coffee_cups):
    print(f"{size} Coffee Cup:")
    print(cup)
