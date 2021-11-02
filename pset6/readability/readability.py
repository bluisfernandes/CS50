from cs50 import get_string

text = get_string("Text: ")

# number of sentences on text
sentences = 0
for word in text.split():
    if word[-1] == '.' or word[-1] == '!' or word[-1] == '?':
        sentences += 1

# l: number of letters on text.
l = 0
for letter in text:
    if letter.isalpha():
        l += 1

# L is the average number of letters per 100 words in the text
L = l / len(text.split()) * 100

# S is the average number of sentences per 100 words in the text
S = sentences / len(text.split()) * 100

index = 0.0588 * L - 0.296 * S - 15.8

# prints the result
if index > 16:
    print(f"Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {round(index)}")