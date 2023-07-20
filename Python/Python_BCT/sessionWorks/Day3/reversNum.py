# Write a program to reverse a number

# Path: sessionWorks\Day3\reversNum.py

temp = num = eval(input("Enter a number: "))
rev = 0

while temp> 0:
    rev = rev*10 + temp%10
    temp = temp//10

print("Reverse of", num, "is", rev)