# 13. Write a Python program to find value of sin series using function.
import math

def sinSeriesCalc(x, n):
    if n == 1:
        return x
    else:
        return ((-1)**(n-1) * x**(2*n-1)) / math.factorial(2*n-1) + sinSeriesCalc(x, n-1)

x,n = eval(input("Enter x and n: "))
print(f"sin({x}) upto {n} term = {sinSeriesCalc(x, n)}")