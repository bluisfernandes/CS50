import csv
from cs50 import get_string
import sys


def main():
    while True:
        option = get_string("Press:\ns - search a name \nr - read all the names \na - add new\nq - quit: ").lower()
        if option == "r" or option == "s" or option == "a" or option == "q":
            break

    if option == "r":
        read()
    if option == "s":
        search()
    elif option == "a":
        add()
    elif option == "q":
        sys.exit(0)

    print("------\n")
    
    main()


def search():
    searched_name = get_string("What's the name to search? ")
    with open("phonebook.csv", "r") as file:
        for line in file:
            if searched_name == line.split(",")[0]:
                print(line.split(",")[0], end=" \t\t")
                print(line.split(",")[1][:-2])
                

def read():
    name_list={}
    with open("phonebook.csv", "r") as file:
        print("\nNames: \t\tNumbers:")
        for line in file:
            print(line.split(",")[0], end=" \t\t")
            print(line.split(",")[1][:-2])


def add():
    with open("phonebook.csv", "a") as file:
        name = get_string("Name: ")
        number = get_string("Number: ")
        writer = csv.writer(file)
        writer.writerow([name, number])
    print(f"{name} added to the file")


main()