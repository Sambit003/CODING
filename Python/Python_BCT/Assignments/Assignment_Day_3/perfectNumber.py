# Perfect Number Check using While Loop

number = int(input("Enter the number: "))
i = 1
sum = 0
while i < number:
    if number % i == 0:
        sum += i
    i += 1
if number == sum:
    print(number, "is a perfect number")
else:
    print(number, "is not a perfect number")
