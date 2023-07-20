# 7. Write a Python program to calculate the factorial of a number using a recursive function.

def factRecur(num):
    if num == 0:
        return 1
    else:
        return num * factRecur(num - 1)
    
num = int(input("Enter a number: "))
print(f"{num}! = {factRecur(num)}")