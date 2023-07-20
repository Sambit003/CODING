# 9. Write a Python program to print all odd and even numbers between 1 to n and also print their sum.

up_term = int(input("Enter the upper limit: "))

odd_sum = 0
even_sum = 0
odd_list = []
even_list = []

for i in range(1, up_term+1):
    if i % 2 == 0:
        even_list.append(i)
        even_sum += i
    else:
        odd_list.append(i)
        odd_sum += i

print(f"Odd numbers between 1 and {up_term} are: {odd_list} & their sum is {odd_sum}")
print(f"Even numbers between 1 and {up_term} are: {even_list} & their sum is {even_sum}")
