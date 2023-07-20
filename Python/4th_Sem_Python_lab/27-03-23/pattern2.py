'''
Write a python program to print the following pattern:
1
2 2
3 3 3
4 4 4 4
5 5 5 5 5
'''

row = int(input("Enter number of rows: "))
for i,j in enumerate(range(row)):
    print(f"{i+1} " * (i+1))