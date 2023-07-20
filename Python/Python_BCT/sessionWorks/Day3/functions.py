"""def add():
    a, b = eval(input("Enter two numbers: ")).split()
    print(a+b)

def div():
    a, b = eval(input("Enter two numbers: ")).split()
    print(a/b)"""

def mul():  
    a, b = eval(input("Enter two numbers: "))
    print(a*b)
mul()

'''x, y = eval(input("Enter two numbers: ")).split()
def multiply(x, y):
    mul = x * y
    return mul
print("Result",multiply(x, y))'''

def fact():
    n = int(input("Enter a number: "))
    f = 1
    for i in range(1, n+1):
        f = f*i
    return f
print("Factorial is", fact())