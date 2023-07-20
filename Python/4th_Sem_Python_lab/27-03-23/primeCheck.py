#5. Write a Python program to check whether a number is Prime number or not.

num = int(input("Enter a number: "))
isPrime = True # flag variable type of boolean
for i in range(2, num):
    if num % i == 0:
        isPrime = False
        break

if isPrime:
    print(f"{num} is a prime number")
else:
    print(f"{num} is not a prime number")