# Factorial using while loop

number = int(input("Enter the number: "))

factorial = 1
i = 1
while i <= number:
    factorial = factorial * i
    i += 1

print("Factorial of", number, "is", factorial)