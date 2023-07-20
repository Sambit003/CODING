# 10. Write a Python program to find power of a number using function.

def powerCalc(number, power):
    if power == 0:
        return 1
    else:
        return number * powerCalc(number, power-1)

number, power = eval(input("Enter a number and its power: "))
print(f"{number}^{power} = {powerCalc(number, power)}")