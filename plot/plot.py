import matplotlib.pyplot as plt

file_path = 'points.dat'
with open(file_path, 'r') as file:
    num_points = int(file.readline().strip())
    lines = file.readlines()

points = [tuple(map(float, line.strip().split())) for line in lines]

if num_points != len(points):
    raise ValueError("Number of points specified in the file does not match the actual number of points.")

x_coordinates, y_coordinates = zip(*points)

plt.scatter(x_coordinates, y_coordinates, color='blue', marker='o')
plt.title('Scatter Plot of Points')
plt.xlabel('X Coordinate')
plt.ylabel('Y Coordinate')
plt.grid(True)
plt.show()
