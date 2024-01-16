import matplotlib.pyplot as plt
import re

file_path_points = 'points.dat'
file_path_order = 'order.dat'

with open(file_path_points, 'r') as file:
    num_points = int(file.readline().strip())
    lines = file.readlines()

points = [tuple(map(float, line.strip().split())) for line in lines]
if num_points != len(points):
    raise ValueError("Number of points specified in the file does not match the actual number of points.")

x_coordinates, y_coordinates = zip(*points)

with open(file_path_order, 'r') as order_file:
    order_lines = order_file.readlines()

order_lists = []
for order_str in order_lines:
    order = list(map(int, re.findall(r'\d+', order_str)))
    order_lists.append(order)

for idx, order_list in enumerate(order_lists, start=1):
    plt.figure(figsize=(8, 6))

    plt.scatter(x_coordinates, y_coordinates, color='blue', marker='.')

    for i in range(-1, len(order_list) - 1):
        plt.plot([x_coordinates[order_list[i]], x_coordinates[order_list[i + 1]]],
                 [y_coordinates[order_list[i]], y_coordinates[order_list[i + 1]]], color='red')

    plt.title(f'Scatter Plot with Line Segments - Order List {idx}')
    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')
    plt.grid(True)

plt.show()
