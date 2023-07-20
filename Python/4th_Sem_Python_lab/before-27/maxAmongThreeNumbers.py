a,b,c = eval(input("Enter three numbers: "))
if a==b==c:
    print("\n\tAll are equal.")
elif a>b and a>c:
    print("\n\t",a," is the largest.")
elif b>a and b>c:
    print("\n\t",b," is the largest.")
else:
    print("\n\t",c," is the largest.")