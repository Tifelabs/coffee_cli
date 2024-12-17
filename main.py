# Ask user for their name
username = input("Enter your name: ")

# Confirm the user's input
confirmation = input(f"Are you sure your name is {username.upper()}? (yes or no): ")

# Validating the user's response
if confirmation.lower() == "yes":
    print("WELCOME!")
elif confirmation.lower() == "no":
    print("Please re-enter your name.")
else:
    print("Invalid command! Please enter 'yes' or 'no'.")

# Coffee options
coffee_names = [
    "Espresso",
    "Latte",
    "Cappuccino",
    "Americano",
    "Mocha",
    "Macchiato",
    "Flat White",
    "Affogato",
    "Irish Coffee",
    "Cold Brew"
]

# Display coffee menu
print("\nWhat coffee do you want to buy?")
print("Available options:")
for index, coffee in enumerate(coffee_names, start=1):
    print(f"{chr(64 + index)}. {coffee}")  # A = 65 in ASCII, B = 66, etc.

# Get user selection
selection = input(f"\nHello {username}, enter coffee type by selecting A, B, C, etc.: ").upper()

# Validate selection and display chosen coffee
if selection in [chr(65 + i) for i in range(len(coffee_names))]
    chosen_coffee = coffee_names[ord(selection) - 65]  
    print(f"\nYou selected {chosen_coffee}. Enjoy your coffee!")
else:
    print("\nInvalid selection. Please try again.")
