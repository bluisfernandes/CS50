from cs50 import get_int


def main():
    
    # prompts the user to asingn the heigth
    while True:
        height = get_int("Heigth:")
        if height > 0 and height <= 8:
            break
    
    # call a function to draw, passing the spaces and briks
    for i in range(height):
        print_line(height - i - 1, i + 1)


# function to print
def print_line(space, brick):
    print(" " * space, end="")
    print("#" * brick, end="")
    print(" " * 2, end="")
    print("#" * brick)


main()