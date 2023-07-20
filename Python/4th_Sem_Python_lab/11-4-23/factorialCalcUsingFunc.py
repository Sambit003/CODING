# 4. Write a Python program to calculate factorial of a number using function.

def factorial(number):
    if number == 0:
        return 1
    else:
        return number * factorial(number-1)

number = int(input("Enter a number: "))
print(f"Factorial of {number} is {factorial(number)}")