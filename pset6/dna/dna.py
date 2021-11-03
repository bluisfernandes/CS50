from cs50 import get_string
import csv
import sys

if len(sys.argv) != 3:
    print("Usage: dna.py database sequence")
    sys.exit(0)

people = []
person = {}
head = []
head_bool = True

with open(sys.argv[1], "r") as file:
    for line in file:
        line = line[:-1]
        
        if head_bool:
            for j in (line.split(",")):
                    head.append(j)
            head_bool = False
            
        for i in range(len(line.split(","))):
            print(f"dict[{head[i]}] == {line.split(',')[i]}")
            person[head[i]] = line.split(',')[i]
            # print(f"{person[head[i]]} is: {line.split(',')[i]}")
        print("XXX ")
        people.append(person)
        print(people)
            
        
print("______")
        
for i in head:
    print(i)
        # person[]
        # for sequence in len(line.split(","):
        #     person[] = line.split(",")[sequence]
        

# with open(sys.argv[2], "r") as file:
#     for line in file:
#         print(line[:-1])

print("______")
print(people)
print("_x____")

for i in people:
    print(i["name"])