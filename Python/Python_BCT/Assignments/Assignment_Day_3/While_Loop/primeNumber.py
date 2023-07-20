# Prime Number checker using While Loop

number = int(input("Enter the number: "))
i = 2
while i < number:
    if number % i == 0:
        print(number, "is not a prime number")
        break
    i += 1
else:
    print(number, "is a prime number")
