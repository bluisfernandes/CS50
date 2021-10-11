from cs50 import get_string
import sys


def main():
    # prompts user to input credit card number
    number = get_string("Number: ")

    # checks if the number is valid
    check_number(number)

    # checks and prints the company
    print_company(number)


# input with string
def check_number(number):
    luhn_aux = 0
    luhn = 0

    # adds 2x digits, beggining with the second-last
    for i in range(-2, -len(number) - 1, -2):
        luhn_aux = 2 * int(number[i])

        # sum each digit
        if luhn_aux >= 10:
            luhn += luhn_aux % 10 + 1
        else:
            luhn += luhn_aux

    # adds the other digits
    for i in range(-1, -len(number) - 1, -2):
        luhn += int(number[i])

    # checks if the last digit is 0, if not, exit the program.
    if luhn % 10 != 0:
        print("INVALID")
        sys.exit(0)


def print_company(number):
    ''' AMEX numbers start with 34 or 37;
        MasterCard numbers start with 51, 52, 53, 54, or 55
        Visa numbers start with 4'''

    digits_2 = int(number[0]) * 10 + int(number[1])
    if digits_2 == 34 or digits_2 == 37:
        print("AMEX")
    elif digits_2 >= 51 and digits_2 <= 55:
        print("MASTERCARD")
    elif digits_2 >= 40 and digits_2 <= 49:
        print("VISA")
    else:
        print("INVALID")


main()

