import numpy as np
import matplotlib.pyplot as plt

dimentions = 11

# Opening file and reading data
fileData = open('data.txt', 'r')
data = fileData.read()

# Value array
dataArray = np.array([])
num = ''

# Reading chars to the array as floats
for char in data:
    if char != ' ':
        num += char
    else:
        dataArray = np.append(dataArray, float(num))
        num = ''

# Separating matrix dimentions (1st two elements) from the data array
K = int(dataArray[0] + 1) # Time t dimention
M = int(dataArray[1] + 1) # Coordinate x dimention

# Removing matrix dimentions from the data array and reshaping the array
dataArray = np.delete(dataArray, [0, 1], None)
dataArray = dataArray.reshape((K, M))

# Time t and coordinate x
t = [[i for i in range(1, K + 1)] for i in range(K)]
x = [[i] * M for i in range(1, M + 1)]

# Plotting
fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')
ax.plot_surface(t, x, dataArray, cmap = 'plasma')
plt.show()