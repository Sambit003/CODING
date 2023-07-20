x,n = eval(input("\tEnter the value of x,n to evaluate Y(x,n): "))
if n==1:
    print("\tBased on your input of n, Y(x,n) = ", (1+(x*x)))
elif n==2:
    print("\tBased on your input of n, Y(x,n) = ", (1+(x/n)))
elif n==3:
    print("\tBased on your input of n, Y(x,n) = ", (1+(2*x)))
else:
    print("\tBased on your input of n, Y(x,n) = ", (1+(n*x)))