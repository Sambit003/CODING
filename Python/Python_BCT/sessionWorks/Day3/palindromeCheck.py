# Write a program to check if a number is a palindrome or not

# Path: sessionWorks\Day3\palindromeCheck.py

temp = num = eval(input("Enter a number: "))
rev = 0

while temp> 0:
    rev = rev*10 + temp%10
    temp = temp//10

if num == rev:
    print(num, "is a palindrome")
else:
    print(num, "is not a palindrome")