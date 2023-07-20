# write a program to print the factorial of each individual function parameters

def fact(*num):
    for n in num:
        f=1
        for i in range(1,n+1):
            f=f*i
        print("Factorial of",n,"is",f)
    
fact(1,2,3,4,5,6,7,8,9,10)