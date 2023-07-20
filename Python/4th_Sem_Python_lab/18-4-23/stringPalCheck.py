# 4. Write a Python program to check whether a string is palindrome or not without using any function or slice operator.

def palindrome(string):
    rev = ""
    for i in range(len(string) - 1, -1, -1):
        rev += string[i]
    if rev == string:
        return True
    else:
        return False
    
string = input("Enter a string: ")

if palindrome(string):
    print("The string is a palindrome")
else:
    print("The string is not a palindrome")