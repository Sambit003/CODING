'''
Write a program to find the sum of the series 1 + 2^2/2! + 3^3/3! + 4^4/4! + 5^5/5! + 6^6/6! + 7^7/7! + 8^8/8! + 9^9/9! + ... + n^n/n!
'''

import math

terms = int(input("Enter the value of terms: "))
sum = 0

for i in range(1, terms+1):
    sum += math.pow(i, i) / math.factorial(i)

print(f"The sum of the series is upto {terms} terms: {sum}")