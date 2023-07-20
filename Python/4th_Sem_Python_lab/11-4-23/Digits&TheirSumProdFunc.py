# 8. Write a Python program to count number of digits in a number and also their sum and product using function.

def digitsOps(number):
    count = 0
    sum = 0
    product = 1

    while number > 0:
        count += 1
        sum += number % 10
        product *= number % 10
        number //= 10

    return count, sum, product

number = int(input("Enter a number: "))
count, sum, product = digitsOps(number)

print(f"Number of digits in {number} is {count} \n Sum of digits: {sum} \n Product of digits: {product}")