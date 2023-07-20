# Write a program to calculate area, perimeter of parallelogram

#input base, slant length, height
base, slantLength, height = eval(input("\tEnter base, slant length, height of parallelogram: "))

#calculate area
area = base * height

#calculate perimeter
perimeter = 2 * (base + slantLength)

#print area and perimeter
print("\tArea of parallelogram is: ", area, ";\t perimeter is: ", perimeter)