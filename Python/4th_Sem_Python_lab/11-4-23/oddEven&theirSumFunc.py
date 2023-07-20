# 9. Write a Python program to print all odd and even numbers between 1 to n and also print their sum.

def oddEven(upper_bound):
    odd_sum = 0
    even_sum = 0
    print(f"Odd numbers from 1 to {upper_bound} are: ", end=" ")
    for i in range(1, upper_bound+1):
        if i % 2 != 0:
            print(i, end=" ")
            odd_sum += i
    print("\nSum of odd numbers is:", odd_sum)
    print("Even numbers from 1 to", upper_bound, "are: ", end=" ")
    for i in range(1, upper_bound+1):
        if i % 2 == 0:
            print(i, end=" ")
            even_sum += i
    print("\nSum of even numbers is:", even_sum)

upper_bound = int(input("Enter a number: "))
oddEven(upper_bound)