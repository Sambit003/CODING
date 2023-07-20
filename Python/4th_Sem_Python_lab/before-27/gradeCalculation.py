marks= int(input("Enter your marks "))
if marks>= 0 and marks<= 100:
    if marks>= 90:
        print("Grade: O")
    elif marks>= 80:
        print("Grade: E")
    elif marks>= 70:
        print("Grade: A")
    elif marks>= 60:
        print("Grade: B")
    elif marks>= 50:
        print("Grade: C")
    elif marks>= 40:
        print("Grade: D")
    else:
        print("Grade: F")
else:
    print("Invalid marks")