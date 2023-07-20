# 3. Write a Python program to reverse a string without using any function or slice operator.

def stringRev(string):
    rev = ""
    for i in range(len(string) - 1, -1, -1):
        rev += string[i]
    return rev

string = input("Enter a string: ")

print(f"Reverse of the string is {stringRev(string)}")