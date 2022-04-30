import numpy as np
import matplotlib.pyplot as plt

# Opening file and reading data
fileData = open('data.txt', 'r')
data = fileData.read()

# Data array
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

# Generating time t and coordinate x grids
t = np.array([[i for i in range(1, K + 1)] for i in range(K)])
x = np.array([[i] * M for i in range(1, M + 1)])

print(t)
print(x)

# Plotting
fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')

#T, X = np.meshgrid(t, x)

ax.plot_surface(t, x, dataArray, cmap = 'plasma')

ax.set_xlabel('Label')
ax.set_ylabel('Label')
ax.set_zlabel('Label')

plt.show()