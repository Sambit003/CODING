'''
Write a program to print a solid diamond pattern of stars.
     *
    ***
   *****
  *******
 *********
***********
 *********
  *******
   *****
    ***
     *
'''


n = int(input("Enter number of rows: "))

# Output: solid diamond pattern
for i in range(1,n+1):
    print(" "*(n-i)+"*"*(2*i-1))

for i in range(n-1,0,-1):
    print(" "*(n-i)+"*"*(2*i-1))
