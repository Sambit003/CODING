#Swapping uwithout using third variable & normal swapping
a,b = eval(input("Enter numbers in a,b: "))
a = a+b
b = a-b
a = a-b
print("\tSwapping without using third variable: \n\tIn a: ",a, "\n\tIn b: ",b)

#Swapping using feature of python
a,b = eval(input("Enter numbers in a,b: "))
a,b = b,a
print("\tSwapping using feature of python: \n\tIn a: ",a, "\n\tIn b: ",b)