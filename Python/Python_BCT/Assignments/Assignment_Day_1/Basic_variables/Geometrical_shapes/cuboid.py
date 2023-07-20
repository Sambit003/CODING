# Write a program to calculate area, perimeter, volume of cuboid

#input length, breadth, height
length, breadth, height = eval(input("Enter length, breadth, height of cuboid: "))

#calculate area
area = length * breadth

#calculate perimeter
perimeter = 2 * (length + breadth)

#calculate volume
volume = length * breadth * height

#print area, perimeter and volume
print("Area of cuboid is: ", area, ";\t perimeter is: ", perimeter, ";\t volume is: ", volume)