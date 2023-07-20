# Write a program to calculate area, perimeter of ellipse

import math

#input major axis and minor axis
majorAxis, minorAxis = eval(input("\tEnter major axis and minor axis of ellipse: "))

#calculate area
area = 3.14 * majorAxis * minorAxis

#calculate perimeter
perimeter = 2 * 3.14 * (math.sqrt((math.pow(majorAxis,2) + math.pow(minorAxis,2))/2))

#print area and perimeter
print("\tArea of ellipse is: ", area, ";\t perimeter is: ", perimeter)