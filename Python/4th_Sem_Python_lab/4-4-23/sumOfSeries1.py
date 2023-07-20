'''
Write a program to find the sum of the series 1 + 1/2 + 1/3 + 1/4 + 1/5 + 1/6 + 1/7 + 1/8 + 1/9 + ... + 1/n
'''

terms = int(input("Enter the value of terms: "))

sum = 0
for i in range(1, terms+1):
    sum += 1/i

print(f"The sum of the series is upto {terms} terms: {sum}")
