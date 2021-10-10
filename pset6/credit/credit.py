from cs50 import get_string


def main():
    # prompts user to input credit card number
    number = get_string("Number: ")

    # checks the company
    check_company(number)

    arroz = 1234;

    print( arroz % 10)
    print( arroz % 100)
    print("----")


def check_company(number):
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

