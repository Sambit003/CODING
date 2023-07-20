# 18. Write a Python Program to read an array of names and to set them in alphabetical order using function.

def alphabeticalOrderName(names):
    for i in range(len(names)):
        for j in range(i+1, len(names)):
            if names[i] > names[j]:
                names[i], names[j] = names[j], names[i]
    return names

names = []
n = int(input("Enter number of names: "))
for i in range(n):
    names.append(input("Enter name: "))
print(f"Names in alphabetical order are: {alphabeticalOrderName(names)}")