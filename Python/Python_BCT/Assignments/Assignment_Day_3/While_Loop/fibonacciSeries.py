# Fibonacci Series print using While Loop

terms = int(input("Enter the number of terms: "))
term1 = 0
term2 = 1

print("Fibonacci Series: ", end="  ")

i = 0
while i < terms:
    if i == 0:
        print(term1, end="  ")
        i += 1
    elif i == 1:
        print(term2, end="  ")
        i += 1
    else:
        term3 = term1 + term2
        print(term3, end="  ")
        term1 = term2
        term2 = term3
        i += 1
