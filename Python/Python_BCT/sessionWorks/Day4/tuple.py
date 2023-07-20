color = ('red', 'green', 'blue', 'mango')


# Unpacking method
t1, t2, t3, t4 = color

t4='black'

color = (t1, t2, t3, t4)

# Typecasting method
colorList = list(color)
colorList[3] = 'black'
color = tuple(colorList)

