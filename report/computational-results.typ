#import "tables.typ": *

= Computational results

== Cplex results
The following tables show the results obtained with cplex. Most of them are exact solution, but some (marked with \*) are sub-optimal solutions obtained after 45 minutes of computation.

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
In order to perform parameters calibration, the instances of the problem have been divided in 2 groups.
In particular 3 instances for each size of the input (25, 50, 75, 100) and the insstance with size 200 are used for calibration and the remaining are used for the final benchmark.
The strategy adopted to calibrate parameters is to calibrate the tabu-list length first and then the remaining parameters.
For the rest of this section, the size of the instance will be called $n$.

=== TS1
In the first attempt, the following parameters have been chosen.
- Tabu-list size: $n$;
- Stopping criteria: max-iterations;
- max-iterations: $50 n$;
- Initial solution: Non-random (@non-random-initial-solution).

=== TS2
In the second attempt, it has been tried to reduce the size of the tabu-list. 
It is easy to notice that none of the solutions is better with respect to the previous one (@relative-errors).
- Tabu-list size: $sqrt(n)$;
- Stopping criteria: max-iterations;
- max-iterations: $50 n$;
- Initial solution: Non-random (@non-random-initial-solution).

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
- Initial solution: Non-random (@non-random-initial-solution)

=== TS4
At this step, tabu-list length is stil increased.
Good improvements are found in half of the test cases.
- Tabu-list size: $n sqrt(n)$;
- Stopping criteria: max-iterations;
- max-iterations: $50 n$.
- Initial solution: Non-random (@non-random-initial-solution)

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
- Initial solution: Non-random (@non-random-initial-solution)

=== TS6
Since continuing to increase the size of the tabu-list was not improving the solutions (experiments that are not reported here), in this test it has been tried to refine the number of iterations and the stopping criteria.
The previous value for the number of iteration was already balnced and the new one has similar results, probably bigger instances are required in order to understand which is better.
- Tabu-list size: $n^2$;
- Stopping criteria: max-non-increasing-iterations;
- max-non-increasing-iterations: $n^2 / 4$.
- Initial solution: Non-random (@non-random-initial-solution)

#figure(
    grid(
        columns: 2,
        gutter: 2mm,
        ts5, ts6
    ),
    caption: "TS5 and TS6 results"
)

== TS7
Finally it has been tried to see whether a random initial solution can be better than an initial solution with parts grouped like in @non-random-initial-solution. Since the inital solution is selected at random, the tests have been run 5 times and the results shown in @ts7-table are an average.
The results show that 5 test cases have a better solution and 7 have a worst one, so a good approach can be mixing random initial paths with non-random.
- Tabu-list size: $n^2$;
- Stopping criteria: max-iterations;
- max-iterations: $50 n$.
- Initial solution: Random


#figure(
    ts7,
    caption: "TS7 results"
) <ts7-table>

=== Relative percentage errors overview

#figure(
  errors,
  caption: "Relative percentage errors"
) <relative-errors>

== Final results
To perform the final benchmark, the most promising parameters have been selected:
- Tabu-list size: $n^2$;
- Stopping criteria: max-iterations;
- max-iterations: $50 n$.
- Initial solution: Non-random (@non-random-initial-solution)
Results show that the solutions have a relative-percentage-error (RPE) lower than 1 in the 71% of the instances, an RPE between 1 and 5 in the 25% of the instances and just one instance has an RPE greater than 5 (6.27%).
Parameters calibration phase has shown that a random inital path may find a better solution, so an idea to improve the current algorithm may be to run the tabu search also with some random paths and keep the better solution. Obviously this approach will cost more in term of time.

#figure(
        grid(
        columns: 2,
        gutter: 2mm,
        results1_error, results2_error
    ),
    caption: "Final results"
)