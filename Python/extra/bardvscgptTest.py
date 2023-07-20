# This one is by bard
def is_prime(n):
  #Returns True if n is a prime number, False otherwise.
  for i in range(2, n):
    if n % i == 0:
      return False
  return True

def prime_factors_bard(n):
  #Returns a list of the prime factors of n.
  factors = []
  for i in range(2, int(n**0.5) + 1):
    while n % i == 0:
      factors.append(i)
      n //= i
  if n > 1:
    factors.append(n)
  return factors

number = int(input("Enter a number: "))
factors = prime_factors_bard(number)
print("The prime factors of {} are: {}".format(number, factors))

# this one is by chatGPT
def prime_factors_chatgpt(n):
    factors = []
    i = 2
    while i * i <= n:
        if n % i:
            i += 1
        else:
            n //= i
            factors.append(i)
    if n > 1:
        factors.append(n)
    return factors

number = 15683615
prime_factors_list = prime_factors_chatgpt(number)

print("Prime factors of", number, "are:", prime_factors_list)
