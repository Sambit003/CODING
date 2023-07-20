num = int (input ("Enter a number: "))

def is_prime (n):
    if n == 1:
        return False
    for i in range (2, n):
        if n % i == 0:
            return False
    return True

def print_prime_factors (n):
    print(f"The prime factors of {n} are: ", end="")
    for i in range (1, n+1):
        if n % i == 0 and is_prime (i):
            print (i, end=" ")

print_prime_factors (num)