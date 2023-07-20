# Write a Python program to get the largest number from three numbers given by user.

# Input: 3 numbers
num1, num2, num3 = eval(input("Enter three numbers: "))

# Process: find the largest number using elif
if num1 > num2 and num1 > num3:
    largest = num1
elif num2 > num1 and num2 > num3:
    largest = num2
elif num1==num2 and num1==num3:
    largest = "All numbers are equal"
else:
    largest = num3

# Output: largest number
print("Largest number is", largest)