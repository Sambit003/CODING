# write a program to calculate the area, perimeter of a rectangle

# input length and breadth
length, breadth = eval(input("Enter length and breadth of rectangle: "))

# calculate area
area = length * breadth

# calculate perimeter
perimeter = 2 * (length + breadth)

# print area and perimeter
print("Area of rectangle is: ", area, "and perimeter is: ", perimeter)