import math

x, term = eval(input("Enter the value of x and terms: "))

sum = 0
for i in range (1, term+1, 2):
    if(i % 2 == 0):
        sum -= math.pow(x, i) / math.factorial(i)
    else:
        sum += math.pow(x, i) / math.factorial(i)

print(f"The sum of the series is: {sum}")