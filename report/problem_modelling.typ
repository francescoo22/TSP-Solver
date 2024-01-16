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

== Problem representation
- A `Graph` is represented as a matrix of dimensions $n times n$ where $n$ is the number of holes and `graph[i][j]` is the euclidean distance between holes `i` and `j`.
- A `Path` represents a solution to the problem, the path is represented as a list of integer.
- A `Point` represents an hole on the motherboard and is represented as a pair of doubles.

=== Example

#figure(
  image("images/graph_sample.png", width: 80%),
  caption: [Graph example],
) <Graph>

#v(2em)

The graph in the @Graph corresponds to the following points:
$
(1, 1);
(2, 5);
(3, 3);
(6, 4);
(2, 7);
(5, 5);
(6, 6);
(8, 2);
(4, 2);
(5, 2)
$

And is represented in this way:
$ [0.00, 4.12, 2.83, 5.83, 6.08, 5.66, 7.07, 7.07, 3.16, 4.12]; \
  [4.12, 0.00, 2.24, 4.12, 2.00, 3.00, 4.12, 6.71, 3.61, 4.24]; \
  [2.83, 2.24, 0.00, 3.16, 4.12, 2.83, 4.24, 5.10, 1.41, 2.24]; \
  [5.83, 4.12, 3.16, 0.00, 5.00, 1.41, 2.00, 2.83, 2.83, 2.24]; \
  [6.08, 2.00, 4.12, 5.00, 0.00, 3.61, 4.12, 7.81, 5.39, 5.83]; \
  [5.66, 3.00, 2.83, 1.41, 3.61, 0.00, 1.41, 4.24, 3.16, 3.00]; \
  [7.07, 4.12, 4.24, 2.00, 4.12, 1.41, 0.00, 4.47, 4.47, 4.12]; \
  [7.07, 6.71, 5.10, 2.83, 7.81, 4.24, 4.47, 0.00, 4.00, 3.00]; \
  [3.16, 3.61, 1.41, 2.83, 5.39, 3.16, 4.47, 4.00, 0.00, 1.00]; \
  [4.12, 4.24, 2.24, 2.24, 5.83, 3.00, 4.12, 3.00, 1.00, 0.00] $

#figure(
  image("images/path_sample.png", width: 80%),
  caption: [Path example],
) <Path>

#v(2em)

Finally the path in the @Path is represented as follows:
$ [0, 2, 1, 4, 6, 5, 3, 7, 9, 8] $