# 8. Write a Python program to count number of digits in a number and also their sum and product.

temp = num = int(input("Enter a number: "))

count = 0
sum = 0
prod = 1

while temp > 0:
    count += 1
    sum += temp % 10
    prod *= temp % 10
    temp //= 10

print(f"Number of digits in {num} is {count}")
print(f"Sum of digits in {num} is {sum}")
print(f"Product of digits in {num} is {prod}")