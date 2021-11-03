from cs50 import get_string
import csv
import sys

if len(sys.argv) != 3:
    print("Usage: dna.py database sequence")
    sys.exit(1)

people=[]
with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)
    for line in reader:
        people.append(line)
        # print(line)

print("______ sequence:")

with open(sys.argv[2], "r") as file:
    reader = csv.reader(file)
    for line in reader:
        print(line[0])


for i in people:
    print(i["name"])