import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import re

file_path_points = 'points.dat'
file_path_order = 'order.dat'
output_gif_path = 'animated_plot.gif'

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

fig, ax = plt.subplots(figsize=(8, 6))


def update(frame):
    order_list = order_lists[frame]

    plt.clf()
    plt.scatter(x_coordinates, y_coordinates, color='blue', marker='.')

    for i in range(-1, len(order_list) - 1):
        plt.plot([x_coordinates[order_list[i]], x_coordinates[order_list[i + 1]]],
                 [y_coordinates[order_list[i]], y_coordinates[order_list[i + 1]]], color='red')

    # plt.pause(0.0002)


ani = FuncAnimation(fig, update, frames=len(order_lists), repeat=False, cache_frame_data=True)

# Save the animation as a GIF
ani.save(output_gif_path, writer='pillow', fps=60)

# plt.show()
