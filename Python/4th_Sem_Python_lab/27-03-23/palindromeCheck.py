# 2. Write a Python program to check whether a number is palindrome or not

temp = num = int(input("Enter a number: "))

rev = 0
while num > 0:
    rev = rev * 10 + num % 10
    num //= 10

if temp == rev:
    print(f"{temp} is a palindrome number")
else:
    print(f"{temp} is not a palindrome number")
