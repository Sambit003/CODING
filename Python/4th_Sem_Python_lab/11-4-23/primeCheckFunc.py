# 5. Write a Python program to check whether a number is Prime number or not using function.

def isPrime(number):
    if number == 1:
        return False
    else:
        for i in range(2, number):
            if number % i == 0:
                return False
        return True

number = int(input("Enter a number: "))
if isPrime(number):
    print(f"{number} is a prime number.")
else:
    print(f"{number} is not a prime number.")