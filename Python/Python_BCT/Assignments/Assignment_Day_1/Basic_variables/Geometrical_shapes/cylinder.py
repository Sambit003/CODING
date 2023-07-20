# Write a program to calculate area, perimeter, volume of cylinder

#input radius, height
radius, height = eval(input("Enter radius, height of cylinder: "))

#calculate area
area = 2 * 3.14 * radius * height

#calculate perimeter
perimeter = 2 * 3.14 * radius

#calculate volume
volume = 3.14 * radius * radius * height

#print area, perimeter and volume
print("Area of cylinder is: ", area, ";\t perimeter is: ", perimeter, ";\t volume is: ", volume)
