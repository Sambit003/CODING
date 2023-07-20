upper_bound = int(input("Enter the upper limit: "))

print("The perfect numbers in the range are: ", end="")
def is_perfect(n):
    sum = 0
    for i in range(1, n):
        if(n % i == 0):
            sum += i
    return sum == n

for i in range(1, upper_bound+1):
    if(is_perfect(i)):
        print(i, end=" ")
