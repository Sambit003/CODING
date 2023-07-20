# 3. Write a Python program to find all factors of a number.

num = int(input("Enter a number: "))
print(f"Factors of {num} are:", end=" ")
for i in range(1, num+1):
    if num % i == 0:
        print(i, end=" ")