# Armstron Number Check using While Loop

temp = number = int(input("Enter the number: "))
order = 0 
sum = 0

# calculate the order of the number using while loop
while temp > 0:
    order += 1
    temp = temp // 10

# calculate the sum of the digits raised to the power of order using while loop
temp = number
while temp > 0:
    digit = temp % 10
    sum += digit ** order
    temp = temp // 10
    
if number == sum:
    print(number, "is an Armstrong number")
else:
    print(number, "is not an Armstrong number")
