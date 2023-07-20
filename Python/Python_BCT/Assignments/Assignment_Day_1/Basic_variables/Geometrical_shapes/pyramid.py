# Write a program to calculate area, perimeter, volume of pyramid

#input length, breadth, height
length, breadth, height = eval(input("Enter length, breadth, height of pyramid: "))

#calculate area
area = length * breadth

#calculate perimeter
perimeter = 2 * (length + breadth)

#calculate volume
volume = length * breadth * height / 3

#print area, perimeter and volume
print("Area of pyramid is: ", area, ";\t perimeter is: ", perimeter, ";\t volume is: ", volume)