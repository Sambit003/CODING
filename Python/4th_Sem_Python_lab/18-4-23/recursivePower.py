# 6. Write a Python program to calculate the power of a number using a recursive function.

def powerRecur(base, exp):
    if exp == 0:
        return 1
    else:
        return base * powerRecur(base, exp - 1)
    
base, exp = eval(input("Enter base and exponent: "))
print(f"{base}^{exp} = {powerRecur(base, exp)}")