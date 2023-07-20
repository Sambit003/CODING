# 5. Write a Python program to convert all lowercase alphabets to uppercase alphabets and vice versa in a string without using any system defined function.

def caseChange(string):
    newString = ""
    for i in range(len(string)):
        if string[i] >= 'a' and string[i] <= 'z':
            newString += chr(ord(string[i]) - 32)
        elif string[i] >= 'A' and string[i] <= 'Z':
            newString += chr(ord(string[i]) + 32) 
        else:
            newString += string[i]
    return newString

string = input("Enter a string: ")

print(f"The string after case change is {caseChange(string)}")