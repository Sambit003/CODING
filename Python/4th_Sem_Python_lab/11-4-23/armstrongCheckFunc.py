# 6. Write a Python program to check whether a number is Armstrong number or not using function.

def isArmstrong(number):
    temp = number
    sum = 0
    while temp > 0:
        sum += (temp % 10) ** int(len(str(number)))
        temp //= 10
    return number == sum

number = int(input("Enter a number: "))
if isArmstrong(number):
    print(number, "is an Armstrong number.")
else:
    print(number, "is not an Armstrong number.")