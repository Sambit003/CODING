# 3. Write a Python program to find all factors of a number using function.

def factors(number):
    print("Factors of", number, "are: ", end=" ")
    for i in range(1, number+1):
        if number % i == 0:
            print(i, end=" ")

number = int(input("Enter a number: "))
factors(number)