'''
Write a python program to print the following pattern:
*
* *
* * *
* * * *
* * * * *
'''

row = int(input("Enter number of rows: "))
for i,j in enumerate(range(row)):
    print("* " * (i+1))

