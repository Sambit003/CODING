# 1. Write a Python program to find the maximum between three numbers using a function.

def maxOf(num1, num2, num3):
    if num1 > num2 and num1 > num3:
        return num1
    elif num2 > num1 and num2 > num3:
        return num2
    else:
        return num3

num1, num2, num3 = eval(input("Enter three numbers: "))

print(f"Maximum of three numbers is {maxOf(num1, num2, num3)}")
