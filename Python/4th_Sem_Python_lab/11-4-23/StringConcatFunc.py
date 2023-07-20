# 15. Write a Python program to concatenate two strings using function.

def concatenate(string1, string2):
    return string1 + string2

string1 = input("Enter first string: ")
string2 = input("Enter second string: ")

print(f"Concatenated string is: {concatenate(string1, string2)}")