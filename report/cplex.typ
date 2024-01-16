= Cplex solver
The model is implemented and solved with the Cplex APIs by the class `SimplexSolver`.

== Row and columns generation
Rows and columns are created one at a time by the method `setupLP`.
Model implementation is straightforward and there is only one constraint that need some kind of reasoning.

$ sum_(i:(i,k) in A) x_(i k) - sum_(j:(k,j), j != 0) x_(k j) = 1 #h(2cm) forall k in N without {0} $

Since the variables $x_(k k)$ appears on both summations, in order to prevent cplex errors, it is necessary to avoid adding its index twice. Since the coefficient of the variable is 1 on the first summation and -1 on the second one, we can just ignore it. This operation is performed by the following code:

```cpp
for (int i = 0; i < size; i++) {
    if (i == k) continue; // avoid adding x_k_k
    coef.push_back(1);
    idx.push_back(tuple_to_index[{'x', i, k}]);
}
```

== Mapping variables
Variable indexes are stored inside an `std::map<std::tuple<char, int, int>, int>` called `tuple_to_index`. Since `std::map` has complexity of $O(log n)$ for accessing and adding a value, this way of mapping the indexes brings the model generation complexity to $O(n^2 log n)$ while using an `std::vector` would have kept the complexity to $O(n^2)$. It has been decided to use an `std::map` because it makes the code way more readable allowing to use the following syntax to access an index: `tuple_to_index[{'y', i, j}]`. Moreover model generation is not the bottleneck of the cplex solver since the model solution is way more expensive and so the difference between $O(n^2 log n)$ and $O(n^2)$ during the model generation is not relevant.

== Result retrieving
In order to retrieve the results it is necessary to make the opposite of what has been done during the model generation, in fact it is needed to map indexes to variables. To do so it is used an `std::vector<std::tuple<char, int, int>>` called `index_to_tuple`. Moreover the result of the problem should be a `Path` as described before, but since cplex output is just an array of values, some reasoning is neede.

=== Path retrieving algorithm

```cpp
std::vector<double> var_values(index_to_tuple.size()); // vector that will contain cplex result
std::vector<std::pair<int, int>> arcs; // vector with arcs selected by cplex
CPXgetx(env, lp, &var_values[0], 0, var_values.size() - 1);

for (int i = 0; i < var_values.size(); i++) {
    auto [c, a, b] = index_to_tuple[i];
    if (c == 'y' && equal(var_values[i], 1)) {
        arcs.emplace_back(a, b); // an arc is added only if the var is y and the value is 1
    }
}
std::sort(arcs.begin(), arcs.end()); // sort arcs for easier access in the next steps
std::vector<int> ans; // vector to store the result

auto [cur, next] = arcs[0];
// since it is guaranteed that the path is well formed, we can proceed in this way
do {
    ans.push_back(cur);
    cur = next;
    next = arcs[cur].second;
} while (cur != 0);

return Path(ans);
```