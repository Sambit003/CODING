# write a python program to print the number from 1 to 20 using for loop

for i in range (1, 21, 1):
    print(i)

# Write a python program to print the number from 1 to n using for loop

n = eval(input("Enter the value of n: "))

for i in range (1, n+1, 1):
    print(i)


# Write a python program to print the number from n to 11 using for loop

n = eval(input("Enter the value of n: "))

for i in range (n, 10, -1):
    print(i)

# Write a python program to print the all even number from 1 to 20 using for loop in one line

for i in range (11, 56, 2):
    if i%2==0:
        print(i, end=" ")

# Write a python program to print the all even and odd number from 11 to n using for loop

n = eval(input("Enter the value of n: "))
for i in range (11, n+1, 2):
    if i%2==0:
        print(i, "is even", end=" ")
    else:
        print(i, "is odd", end=" ")

# Write a python program to print the factorial of a number using for loop
num = eval(input("Enter a number: "))

fact = 1
if num==0 or num==1:
    print("Factorial is 1")
else:
    for i in range (1, num+1, 1):
        fact = fact * i
    print("Factorial is", fact)

# Write a python program to print the sum of 1 to 10 using for loop

sum = 0
for i in range (1, 11, 1):
    sum = sum + i
print("Sum is", sum)
