#6. Write a Python program to check whether a number is Armstrong number or not

temp = num = int(input("Enter a number: "))

sum = 0

order = len(str(num))

while temp > 0:
    sum += (temp % 10) ** order
    temp //= 10

if num == sum:
    print(f"{num} is an Armstrong number")
else:
    print(f"{num} is not an Armstrong number")