'''
Write a program to print the following pattern
      1
    2 3
  3 4 5
4 5 6 7
'''

rows = int(input("Enter the number of rows: "))
for i in range(rows):
    for j in range(rows - i - 1):
        print(" ", end=" ")
    for j in range(i + 1, i + i + 2):
        print(j, end=" ")
    print()