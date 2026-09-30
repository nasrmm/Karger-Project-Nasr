# Karger-Project-Nasr

Implementation and empirical study of Karger's randomised minimum cut algorithm in C++.

The project implements Karger's contraction algorithm for undirected multigraphs and compares its empirical success probability against the theoretical lower bound and an exact brute-force minimum-cut baseline.

## Project Structure

```text
karger-project/
├── src/
│   ├── dsu.h
│   ├── karger.cpp
│   ├── karger.h
│   └── main.cpp
│
├── plots/
│   └── plot_results.py
│
├── results.csv
├── success_probability.png
├── karger_runtime.png
├── exact_runtime.png
├── README.md
└── .gitignore
```

## Implementation

The graph is represented using an edge list. Parallel edges are preserved because each copy represents a separate possible random choice during contraction.

A disjoint-set union (DSU) structure is used to represent contracted supernodes. An edge survives when its endpoints belong to different DSU components. Edges whose endpoints belong to the same component are self-loops and are ignored.

Each run of Karger's algorithm:

1. Starts with every vertex in its own component.
2. Selects a surviving edge uniformly at random.
3. Contracts its two endpoints using DSU.
4. Repeats until two components remain.
5. Counts the edges crossing between the final two components.

The project also includes an exact brute-force minimum-cut implementation. This is used to determine the true minimum cut for the experimental graphs.

## Graph Families

The experiments use three graph families:

- Cycle graphs
- Complete graphs
- Two-cluster graphs

The two-cluster graphs consist of two complete subgraphs connected by two bridge edges.

## Experiments

For each graph, Karger's algorithm is executed 5,000 times.

A run is counted as successful when the cut returned by Karger's algorithm equals the exact minimum cut calculated by the brute-force baseline.

The experiments record:

- number of vertices
- number of edges
- exact minimum cut
- number of trials
- number of successful Karger runs
- empirical success rate
- theoretical lower bound
- Karger runtime
- exact baseline runtime

Results are written to `results.csv`.

The experiments use a fixed random seed so that results are reproducible.

## Building

The project requires a C++17-compatible compiler.

On macOS, the project can be compiled with:

```bash
SDKROOT=$(xcrun --show-sdk-path)

clang++ -std=c++17 \
  -isysroot "$SDKROOT" \
  -isystem "$SDKROOT/usr/include/c++/v1" \
  src/main.cpp src/karger.cpp \
  -o karger
```

On systems where the standard C++ headers are configured normally, this may be sufficient:

```bash
g++ -std=c++17 src/main.cpp src/karger.cpp -o karger
```

## Running the Experiments

Run:

```bash
./karger
```

To save the output directly to the CSV file:

```bash
./karger > results.csv
```

The output format is:

```text
graph,n,m,trials,min_cut,successes,success_rate,theoretical_bound,karger_time_ms,exact_time_ms
```

## Generating the Plots

The plotting script requires Python 3 with pandas and Matplotlib.

Install the dependencies with:

```bash
python3 -m pip install pandas matplotlib
```

Then run:

```bash
python3 plots/plot_results.py
```

This generates:

```text
success_probability.png
karger_runtime.png
exact_runtime.png
```

## Empirical Study

The main research question is:

> How does the empirical probability that Karger's algorithm finds a minimum cut compare with its theoretical guarantee, and how much does graph structure affect this probability?

The theoretical reference used is:

```text
2 / (n(n - 1))
```

This is a lower bound associated with preserving a particular fixed minimum cut. The empirical experiment instead counts success whenever Karger's algorithm returns any minimum cut.

The experiments show that graph structure has a substantial effect on observed success probability. Cycle graphs achieved a success rate of 1.0 across the tested sizes, while complete and two-cluster graphs produced lower success rates.

See the written report for the full experimental analysis and discussion.

## Notes

The brute-force exact minimum-cut algorithm is intended only as a small-graph baseline. It enumerates possible vertex partitions and therefore has exponential growth.

The Karger implementation is intentionally straightforward: it rebuilds the list of surviving edges during every contraction step. This makes the implementation easier to understand and verify, although more efficient implementations are possible.

## Author

Nasr Mohammed

```

```
