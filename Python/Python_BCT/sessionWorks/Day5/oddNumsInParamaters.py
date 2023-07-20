# Write a program to print the odd numbers in function parameters

def odd(*num):
    for n in num:
        if n%2!=0:
            print(n)
    
odd(1,2,3,4,5,6,7,8,9,10)