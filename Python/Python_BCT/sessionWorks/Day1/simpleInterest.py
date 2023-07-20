#write a python programm to calculate simple interest

#input the principal amount
principal = float(input("Enter the principal amount: "))

#input the rate of interest
rate = float(input("Enter the rate of interest: "))

#input the time
time = float(input("Enter the time: "))

#calculate the simple interest
simpleInterest = (principal * rate * time) / 100

#display the simple interest
print("Simple interest is: ", simpleInterest)

#total amount
totalAmount = principal + simpleInterest

#display the total amount
print("Total amount is: ", totalAmount)