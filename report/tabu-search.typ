= Tabu search

== Design choices
In order to be as efficient as possible, the tabu-list is implemented in the following way:
- an `std::deque<Path>` called `tabu_list` is used to store the paths inside the tabu_list;
- an `std::map<Path, bool>` called `tabu_map` is used to know efficiently which paths are inside the tabu-list.
Considering an input with $n$ holes and a tabu-list of maximum legth $m$ the operations performed on the two data structures have the following complexities:
- $O(n)$ for pushing on the front or popping on the back a path in the tabu-list
- $O(n log m)$ for updating and checking whether a path is in the tabu-list or not.
Using an `std::deque` improves the performance compared to an `std::vector` when pushing on the front because the second has to perform a shift of all the elements with complexity $O(n m)$.
Also using an `std::map` to check whether a path is in the tabu-list improves the performance since iterating over the tabu-list costs $O(n m)$ in the worst case.
Since `std::map` is implemented as a balanced BST, it was also necessary to implement a comparison operator between paths that has been implemented as lexicographic (this is why the complexity of operations on the tabu-map is $O(n log m)$ and not $O(log m)$).

== Initial solution
Since inputs are not completely random, starting from a path in which shapes are grouped together is already a good solution. Grouping parts is obtained for free since the input generation puts them in the right order. This approach is also coherent with the abstract of the problem since a company tha produces motherboards will probably know the parts of the motherboard.
In order to test different approaches, also a randomized initial path has been implemented.

#figure(
  image("images/non_random_start.png", width: 80%),
  caption: [Initial solution with shapes grouped],
)

#figure(
  image("images/random_start.png", width: 80%),
  caption: [Initial random solution],
)
 
== Stopping criteria
The following stopping criteria has been implemented:
- max iterations;
- max non increasing iterations;
- time limit.
Their implementation is straightforward and there are not any interesting design choices.

== Parameters
The parameters that can be calibrated are the following:
- max iterations;
- max non increasing iterations;
- time limit;
- tabu-list length.