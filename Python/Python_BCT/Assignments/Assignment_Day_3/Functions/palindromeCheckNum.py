# Using no return value and no parameters
def palindromeCheck():
    number = int(input("Enter a number: "))
    temp = number
    reverse = 0
    while temp > 0:
        reverse = reverse * 10 + temp % 10
        temp //= 10
    if number == reverse:
        print(number, " is a palindrome")
    else:
        print(number, " is not a palindrome")
palindromeCheck()


# Using return value and no parameters
def palindromeCheck():
    number = int(input("Enter a number: "))
    temp = number
    reverse = 0
    while temp > 0:
        reverse = reverse * 10 + temp % 10
        temp //= 10
    if number == reverse:
        return True
    else:
        return False
if palindromeCheck():
    print(number, " is a palindrome")
else:
    print(number, " is not a palindrome")


# Using no return value and parameters
def palindromeCheck(number):
    temp = number
    reverse = 0
    while temp > 0:
        reverse = reverse * 10 + temp % 10
        temp //= 10
    if number == reverse:
        print(number, " is a palindrome")
    else:
        print(number, " is not a palindrome")
number = int(input("Enter a number: "))
palindromeCheck(number)


# Using return value and parameters
def palindromeCheck(number):
    temp = number
    reverse = 0
    while temp > 0:
        reverse = reverse * 10 + temp % 10
        temp //= 10
    if number == reverse:
        return True
    else:
        return False
number = int(input("Enter a number: "))
if palindromeCheck(number):
    print(number, " is a palindrome")
else:
    print(number, " is not a palindrome")