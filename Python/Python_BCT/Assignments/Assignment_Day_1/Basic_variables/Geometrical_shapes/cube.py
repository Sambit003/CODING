# Write a program to calculate area, perimeter, volume of cube

#input side
side = eval(input("\tEnter side of cube: "))

#calculate area
area = side * side

#calculate perimeter
perimeter = 4 * side

#calculate volume
volume = side * side * side

#print area, perimeter and volume

print("\tArea of cube is: ", area, ";\t perimeter is: ", perimeter, ";\t volume is: ", volume)