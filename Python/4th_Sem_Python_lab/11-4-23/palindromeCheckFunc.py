# 2. Write a Python program to check whether a number is palindrome or not using function.

def palindromeCheck(number):
    temp = number
    reverse = 0
    while temp > 0:
        reverse = reverse * 10 + temp % 10
        temp = temp // 10
    return number == reverse

number = int(input("Enter a number: "))
if palindromeCheck(number):
    print(f"{number} is a palindrome number.")
else:
    print(f"{number} is not a palindrome number.")
