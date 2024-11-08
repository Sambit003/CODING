def print_pattern(n):
    num = 1
    for i in range(1, n + 1):
        # Print leading spaces for triangular shape
        print(" " * (n - i), end="")
        
        # Print numbers with underscores
        for j in range(i):
            if j == i - 1:
                print(num, end="")  # Print the last number in the row without an underscore
            else:
                print(num, end="_")  # Print numbers followed by underscores
            num += 1
        print()  # Move to the next line

# Set the number of rows
n = 4
print_pattern(n)