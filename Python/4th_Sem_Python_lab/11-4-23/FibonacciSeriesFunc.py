# 7. Write a Python program to print Fibonacci series up to n terms using function.

def fibonacci(upper_bound):
    if upper_bound == 1:
        return 0
    elif upper_bound == 2:
        return 1
    else:
        return fibonacci(upper_bound-1) + fibonacci(upper_bound-2)

upper_bound = int(input("Enter terms: "))
print("Fibonacci series up to", upper_bound, "terms is: ", end=" ")
for i in range(1, upper_bound+1):
    print(fibonacci(i), end=" ")