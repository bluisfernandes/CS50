from cs50 import get_string
import csv
import sys


# searchs STR in DNA and returns the number of time they appear
def search(dna, STR):
    quant = 0
    quant_long = 0
    skip = 0
    positions = len(dna) - len(STR) + 1
    for i in range(positions):
        # when found a STR, it skips nexts n nucliotides, n=len(STR)
        if skip > 0:
            skip -= 1
            continue
        
        if dna[i:i+len(STR)] == STR:
            quant += 1
            quant_long = max(quant, quant_long)
            skip = len(STR)-1
        else:
            quant = 0
    return quant_long


# User usage
if len(sys.argv) != 3:
    print("Usage: dna.py database sequence")
    sys.exit(1)

# keeps people in memory
people = []
with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)
    for line in reader:
        people.append(line)

# loads dna to memory
with open(sys.argv[2], "r") as file:
    reader = csv.reader(file)
    for line in reader:
        dna = line[0]

# list of all STRs
str_list = list(people[0].keys())[1:]

# searchs and counts all STR for the person
person = {}
for i in str_list:
    person[i] = search(dna, i)


# print(f"person: {person}")

# find person in database(people)
person_bool = False
for p in people:
    for s in str_list:
        # print(f"{p['name']}|{s}|{p[s]} -> {person[s]}")
        if int(p[s]) != int(person[s]):
            # print(f"\tout: {p[s]} != {person[s]}")
            break
        if s == str_list[-1]:
            print(p["name"])
            person_bool = True
            
# print if there is no match
if person_bool == False:
    print("No match")
