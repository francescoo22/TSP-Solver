= Problem modelling

== Problem description
A company produces boards with holes used to build electric panels. Boards are positioned over a machine and a drill moves over the board, stops at the desired positions and makes the holes. Once a board is drilled, a new board is positioned and the process is iterated many times. Given the position of the holes on the board, the company asks us to determine the hole sequence that minimizes the total drilling time, taking into account that the time needed for making an hole is the same and constant for all the holes.

== Input representation
An instance of the problem is represented as a list of points on the Cartesian plane.
The first line of an input instance contains a single integer $n$, the number of points.
Each of the following $n$ lines contains two doubles separeted by a space.

== Holes generation
The class `InputGenerator` deals with generating an instance of the problem.
Since the abstract of the problem is about making holes on a motherboard, input instances are not generated completely at random, instead, a given number of random shapes representing the components of the motherboard is generated. There are four different shapes (line, rectangle, circle, set of points) and each shape has random dimensions.

#figure(
  image("images/input_instance.png", width: 80%),
  caption: [Input instance example],
)

== Graph representation
A `Graph` is represented as a matrix of dimensions $n times n$ where $n$ is the number of holes and `graph[i][j]` is the euclidean distance between holes `i` and `j`.
A `Path` represents a solution to the problem, the path is represented as a list of integer.