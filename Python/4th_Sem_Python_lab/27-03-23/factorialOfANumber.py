# 4. Write a Python program to calculate factorial of a number

num = int(input("Enter a number: "))

fact = 1
for i in range(1, num+1):
    fact *= i

print(f"Factorial of {num} is {fact}")