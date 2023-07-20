# Write a python program to perform marksheet program

# Input: 5 subjects marks
histor, physics, chemistry, biology, computer = eval(input("Enter 5 subjects marks: "))

# Process: find the total marks and percentage
total = histor + physics + chemistry + biology + computer
percentage = (total / 500) * 100

# Output: total marks and percentage
print("Total marks is", total, "and percentage is", percentage)

if percentage>=60 and percentage<=100:
    print("First division")
elif percentage>=45 and percentage<60:
    print("Second division")
elif percentage>=35 and percentage<45:
    print("Third division")
else:
    print("Better luck next time")