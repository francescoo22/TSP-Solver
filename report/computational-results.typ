#import "tables.typ": *

= Computational results

== Cplex results

#figure(
    grid(
        columns: 2,
        gutter: 2mm,
        cplex25, cplex50, cplex75, cplex100, cplex200
    ),
    caption: "Results of cplex solver"
)

\* sub-optimal solution obtained after 45 minutes of computation

== Tabu search parameter calibration
Tabu search parameters has been calibrated with a subset of the instances shown in the previous section.
In particular it has been taken 3 instances for each size of the input (25, 50, 75, 100) and the insstance with size 200. For the rest of this section, the size of the instance will be called $n$.

=== TS1
In the first attempt, the following parameters are chosen.
- Tabu-list size: $n$;
- Stopping criteria: max-iterations;
- max-iterations: $50 n$.

=== TS2
In the second attempt, it has been tried to reduce the size of the tabu-list. 
It is easy to notice that none of the solutions is better with respect to the previous one.
- Tabu-list size: $sqrt(n)$;
- Stopping criteria: max-iterations;
- max-iterations: $50 n$.

#figure(
    grid(
        columns: 2,
        gutter: 2mm,
        ts1, ts2
    ),
    caption: "TS1 and TS2 results"
)

=== TS3
Since reducing the size of the tabu-list seems not good, this time it has been tried to increase it.
Doing this improves the solution of 3 test cases and makes worst 1 solution if compared to TS1.
- Tabu-list size: $2 n$;
- Stopping criteria: max-iterations;
- max-iterations: $50 n$.

=== TS4
At this step, tabu-list length is stil increased.
Good improvements are found in half of the test cases.
- Tabu-list size: $n sqrt(n)$;
- Stopping criteria: max-iterations;
- max-iterations: $50 n$.

#figure(
    grid(
        columns: 2,
        gutter: 2mm,
        ts3, ts4
    ),
    caption: "TS3 and TS4 results"
)

=== TS5
At this step, tabu-list length is stil increased and 3 small improvements has been found.
It has also been tried to increase the number of iterations, by setting as stopping criteria, max-non-increasing-iterations = $n^2$ but the solution were the same while the execution time increased a lot.
- Tabu-list size: $n^2$;
- Stopping criteria: max-iterations;
- max-iterations: $50 n$.

=== TS6
In the last test it has been tried to refine the number of iterations and the stopping criteria.
The previous value for the number of iteration was already balnced and the new one has similar results, probably bigger instances are required in order to understand which is better.
- Tabu-list size: $n^2$;
- Stopping criteria: max-non-increasing-iterations;
- max-iterations: $n^2 / 4$.

#figure(
    grid(
        columns: 2,
        gutter: 2mm,
        ts5, ts6
    ),
    caption: "TS5 and TS6 results"
)

=== Errors

#figure(
  errors,
  caption: "Relative errors"
)
