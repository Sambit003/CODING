# Strong Number Check using While Loop

number = int(input("Enter the number: "))
temp = number
sum = 0

# calculate the sum of the factorial of the digits using while loop
while temp > 0:
    digit = temp % 10
    factorial = 1
    i = 1
    while i <= digit:
        factorial *= i
        i += 1
    sum += factorial
    temp = temp // 10

if number == sum:
    print(number, "is a Strong number")
else:
    print(number, "is not a Strong number")