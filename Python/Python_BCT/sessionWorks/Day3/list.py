# Write a python program to make a list and store input devices in it. Check the list type and length.

# Take multiple inputs at once
'''inputList = list(input("Enter input devices: "))

print(type(inputList))
print(len(inputList))

rainbowColor = []
for i in range(7):
    rainbowColor.append(input("Enter a color: "))
print(rainbowColor)'''

# Write a python program to square all the numbers in a list.

numList = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

for i in range(len(numList)):
    numList[i] = numList[i]**2

print(numList)

# Write a python program to arrange the list with values in ascending order withoutusing any method/functio.

num = [40, 20, 30, 10, 50, 88, 95, 2, 1, 7, 8, 9, 0, 110, 1967]

for i in range(len(num)):
    for j in range(i+1, len(num)):
        if num[i] > num[j]:
            num[i], num[j] = num[j], num[i]

print(num)