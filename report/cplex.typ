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

== Result retrieving