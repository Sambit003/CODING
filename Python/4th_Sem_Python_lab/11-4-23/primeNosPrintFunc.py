# 11. Write a Python program to print all Prime numbers between 1 to n using function.

def primeNos(upper_bound):
    print("Prime numbers from 1 to", upper_bound, "are: ", end=" ")
    for number in range(1, upper_bound+1):
        if number == 1:
            continue
        else:
            for i in range(2, number):
                if number % i == 0:
                    break
            else:
                print(number, end=" ")

upper_bound = int(input("Enter a number: "))
primeNos(upper_bound)