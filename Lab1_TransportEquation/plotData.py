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

# Separating matrix dimentions (4 front elements) from the data array
T = int(dataArray[0]) # Time limit
X = int(dataArray[1]) # Coordinate limit
K = int(dataArray[2] + 1) # Time t dimention (Number of time points)
M = int(dataArray[3] + 1) # Coordinate x dimention (Number of coordinate points)

# Removing 4 front elements from the data array and reshaping the array
dataArray = np.delete(dataArray, range(4), None)
dataArray = dataArray.reshape(K, M)

tau = T / (K - 1) # Time step
h = X / (M - 1) # Coordinate step

# Creating time and coordinate mesh
tValues = np.array(range(K)) * tau
xValues = np.array(range(M)) * h
tMesh, xMesh = np.meshgrid(xValues, tValues)

# Plotting
fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')

ax.plot_surface(tMesh, xMesh, dataArray, cmap = 'plasma')

ax.set_xlabel('Coordinate, x')
ax.set_ylabel('Time, t')
ax.set_zlabel('Data')

plt.show()