# 1. Write a Python program to print natural numbers from 1 to n and also print their sum using function.

def naturalNumber(upper_bound):
    sum = 0
    print(f"Natural numbers from 1 to {upper_bound} are:", end=" ")
    for i in range(1, upper_bound+1):
        print(i, end=" ")
        sum += i
    print("\nSum is:", sum)

upper_bound = int(input("Enter a number: "))
naturalNumber(upper_bound)