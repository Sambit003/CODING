# 8. Write a Python program to count the total number of vowels and consonants in a string using a function.

def vcCount(string):
    vowels = "aeiouAEIOU"
    vCount = 0
    cCount = 0
    for char in string:
        if char in vowels:
            vCount += 1
        else:
            cCount += 1
    return vCount, cCount

string = input("Enter a string: ")

vCount, cCount = vcCount(string)

print(f"Vowels: {vCount} ; Consonants: {cCount}")