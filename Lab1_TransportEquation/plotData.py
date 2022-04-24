import numpy as np
import matplotlib.pyplot as plt

dimentions = 11

# Opening file and reading data
fileData = open('output.txt', 'r')
data = fileData.read()

# Value array
array = []
num = ''

# Reading chars to the array as floats
for char in data:
    if char != ' ':
        num += char
    else:
        array.append(float(num))
        num = ''

t = [[i for i in range(1,dimentions + 1)] for i in range(dimentions)]
x = [[i] * dimentions for i in range(1, dimentions + 1)]

# Reshaping data
func = np.array(array)
func = func.reshape((dimentions,dimentions))

# Plotting
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(x, t, func, cmap='plasma')
plt.show()