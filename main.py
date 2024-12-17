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


def welcome