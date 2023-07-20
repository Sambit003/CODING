#write a python program to check given number by the user is even or odd 
#input the number
num = eval(input("Enter the number: "))

#check the number is even or odd
if num % 2 == 0:
    print("The number is even")
elif num % 2 != 0:
    print("The number is odd")
else:
    print("The number is neither even nor odd")

