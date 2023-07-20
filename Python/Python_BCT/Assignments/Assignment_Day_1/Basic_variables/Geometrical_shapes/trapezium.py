# Write a program to calculate area, perimeter of trapezium

#input 4 sides
side1, side2, side3, side4 = eval(input("\tEnter 4 sides of trapezium: "))

#input height
height = eval(input("\tEnter height of trapezium: "))

#calculate area
area = (side1 + side2) * height / 2

#calculate perimeter
perimeter = side1 + side2 + side3 + side4

#print area and perimeter
print("\tArea of trapezium is: ", area, ";\t perimeter is: ", perimeter)