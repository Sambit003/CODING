# 2. Write a Python program to check whether a number is even or odd using a function.

def oddEven(num):
    if num % 2 == 0:
        return "Even"
    else:
        return "Odd"
    
num = int(input("Enter a number: "))

print(f"The number is {oddEven(num)}")