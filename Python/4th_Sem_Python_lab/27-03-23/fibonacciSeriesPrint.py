#7. Write a Python program to print Fibonacci series up to n terms.

term = int(input("Enter the number of terms: "))

a = 0
b = 1

print(f"Fibonacci series up to {term} terms is: {a} {b}", end=" ")
for i in range(term - 2):
    c = a + b
    print(c, end=" ")
    a = b
    b = c