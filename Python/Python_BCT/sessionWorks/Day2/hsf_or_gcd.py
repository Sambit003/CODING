# write a program to find the GCD and HCF of two numbers given by user.

# Input: 2 numbers
num1, num2 = eval(input("Enter two numbers: "))

# find the GCD of two numbers
if num1 > num2:
    smaller = num2
else:
    smaller = num1

for i in range (1, smaller+1, 1):
    if num1%i==0 and num2%i==0:
        hcf = i

# Output: HCF of two numbers
print("HCF of two numbers is", hcf)

# find the LCM of two numbers
lcm = (num1 * num2) / hcf

# Output: LCM of two numbers
print("LCM of two numbers is", lcm)