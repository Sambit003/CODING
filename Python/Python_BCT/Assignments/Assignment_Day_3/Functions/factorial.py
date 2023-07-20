# NORMAL LOOP METHOD
# Using no return value and no parameters
def factorial():
    number = int(input("Enter a number: "))
    fact = 1
    for i in range(1, number + 1):
        fact *= i
    print("The factorial of ", number, " is: ", fact)
factorial()


# Using return value and no parameters
def factorial():
    number = int(input("Enter a number: "))
    fact = 1
    for i in range(1, number + 1):
        fact *= i
    return fact
print("The factorial of ", number, " is: ", factorial())


# Using no return value and parameters
def factorial(number):
    fact = 1
    for i in range(1, number + 1):
        fact *= i
    print("The factorial of ", number, " is: ", fact)
number = int(input("Enter a number: "))


# Using return value and parameters
def factorial(number):
    fact = 1
    for i in range(1, number + 1):
        fact *= i
    return fact
number = int(input("Enter a number: "))
print("The factorial of ", number, " is: ", factorial(number))