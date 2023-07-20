#write a program to swap two numbers using third variable

#input the first number
num1 = eval(input("Enter the first number: "))
#input the second number
num2 = eval(input("Enter the second number: "))

#swap the numbers
temp = num1
num1 = num2
num2 = temp

#display the numbers
print("The first number is: ", num1, "\n The second number is: ", num2)

#write a program to swap two numbers without using third variable

#input the first number
num1 = eval(input("Enter the first number: "))
#input the second number
num2 = eval(input("Enter the second number: "))

#swap the numbers
num1, num2 = num2, num1

#display the numbers
print("The first number is: ", num1, "\n The second number is: ", num2)