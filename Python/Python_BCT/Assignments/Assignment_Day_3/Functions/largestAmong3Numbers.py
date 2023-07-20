# Using no return value and no parameters
def largestAmong3Numbers():
    number1, number2, number3 = eval(input("Enter three numbers: "))
    if number1 > number2 and number1 > number3:
        print("The largest number is: ", number1)
    elif number2 > number1 and number2 > number3:
        print("The largest number is: ", number2)
    else:
        print("The largest number is: ", number3)
largestAmong3Numbers()


#  Using return value and no parameters
def largestAmong3Numbers():
    number1, number2, number3 = eval(input("Enter three numbers: "))
    if number1 > number2 and number1 > number3:
        return number1
    elif number2 > number1 and number2 > number3:
        return number2
    else:
        return number3
print("The largest number is: ", largestAmong3Numbers())


# Using no return value and parameters
def largestAmong3Numbers(number1, number2, number3):
    if number1 > number2 and number1 > number3:
        print("The largest number is: ", number1)
    elif number2 > number1 and number2 > number3:
        print("The largest number is: ", number2)
    else:
        print("The largest number is: ", number3)
number1, number2, number3 = eval(input("Enter three numbers: "))
largestAmong3Numbers(number1, number2, number3)


# Using return value and parameters
def largestAmong3Numbers(number1, number2, number3):
    if number1 > number2 and number1 > number3:
        return number1
    elif number2 > number1 and number2 > number3:
        return number2
    else:
        return number3
number1, number2, number3 = eval(input("Enter three numbers: "))
print("The largest number is: ", largestAmong3Numbers(number1, number2, number3))