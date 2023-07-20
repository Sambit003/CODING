# 1. Write a Python program to print natural numbers from 1 to n and also print their sum.

n = int(input("Enter the value of n: "))
sum = 0
print(f"Natural numbers from 1 to {n} are:", end=" ")
for i in range(1, n+1):
    print(i, end=" ")
    sum += i
print(f"Sum of natural numbers from 1 to {n} is {sum}")