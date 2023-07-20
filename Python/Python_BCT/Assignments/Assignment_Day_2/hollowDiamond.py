'''
    Write a program to print the following pattern
    *********
    **** ****
    ***   ***
    **     **
    *       *
    **     **
    ***   ***
    **** ****
    *********
'''

n = eval(input("Enter the number: "))

# Output: hollow diamond pattern
for i in range(1,n+1):
    print("*"*(n+1-i)+" "*(2*i-2)+"*"*(n+1-i))

for i in range(n-1,0,-1):
    print("*"*(n+1-i)+" "*(2*i-2)+"*"*(n+1-i))