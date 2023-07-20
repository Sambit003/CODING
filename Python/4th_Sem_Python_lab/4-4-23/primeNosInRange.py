upper_bound = int(input("Enter the upper limit: "))

print("The prime nos in range are: ", end="")

def is_prime(n):
    for i in range(2, n):
        if(n % i == 0):
            return False
    return True

for i in range(2, upper_bound+1):
    if(is_prime(i)):
        print(i, end=" ")