'''
Write a program to print the following pattern
        *
       **
      ***
     ****
    *****
'''

rows = eval(input("Enter the number of rows: "))

# Output: pattern
for i in range(1, rows+1):
    print(" "*(rows-i)+"*"*(i))
