# Write a program to calculate area, perimeter, volume of cone

import math

#input radius, height
radius, height = eval(input("Enter radius, height of cone: "))

#calculate area
area = 3.14 * radius * (radius + math.sqrt(height * height + radius * radius))

#calculate perimeter
perimeter = 3.14 * radius * (radius + math.sqrt(height * height + radius * radius))

#calculate volume
volume = 1/3 * 3.14 * radius * radius * height

#print area, perimeter and volume
print("Area of cone is: ", area, ";\t perimeter is: ", perimeter, ";\t volume is: ", volume)
