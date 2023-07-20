# 14. Write a Python program to convert lowercase string to uppercase string and vice versa using function.

def caseChange(string):
    for i in range(len(string)):
        if string[i].islower():
            string = string[:i] + string[i].upper() + string[i+1:]
        else:
            string = string[:i] + string[i].lower() + string[i+1:]
    return string

string = input("Enter a string: ")
print(f"Case changed string is: {caseChange(string)}")