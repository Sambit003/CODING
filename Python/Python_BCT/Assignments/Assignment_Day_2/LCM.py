#LCM 
num1, num2 = eval(input("Enter two numbers: "))
if num1 > num2:
    greater = num1
else:
    greater = num2

while True:
    if greater % num1 == 0 and greater % num2 == 0:
        lcm = greater
        break
    greater += 1

print("LCM of two numbers is", lcm)

#HCF
num1, num2 = eval(input("Enter two numbers: "))
if num1 > num2:
    smaller = num2
else:
    smaller = num1

for i in range(1, smaller+1):
    if num1 % i == 0 and num2 % i == 0:
        hcf = i

print("HCF of two numbers is", hcf)