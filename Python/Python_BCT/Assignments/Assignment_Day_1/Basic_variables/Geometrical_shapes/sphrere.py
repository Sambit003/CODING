# Write a program to calculate area, perimeter, volume of sphere

#input radius
radius = eval(input("Enter radius of sphere: "))

#calculate area
area = 4 * 3.14 * radius * radius

#calculate perimeter
perimeter = 4 * 3.14 * radius

#calculate volume
volume = 4/3 * 3.14 * radius * radius * radius

#print area, perimeter and volume
print("Area of sphere is: ", area, ";\t perimeter is: ", perimeter, ";\t volume is: ", volume)