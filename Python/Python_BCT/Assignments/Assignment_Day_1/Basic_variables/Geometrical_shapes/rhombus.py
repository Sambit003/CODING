# Write a program to calculate area, perimeter of rhombus

#input side
side = eval(input("\tEnter side of rhombus: "))

#input diagonals
diagonal1, diagonal2 = eval(input("\tEnter diagonals of rhombus: "))

#calculate area
area = diagonal1 * diagonal2 / 2

#calculate perimeter
perimeter = 4 * side

#print area and perimeter
print("\tArea of rhombus is: ", area, ";\t perimeter is: ", perimeter)