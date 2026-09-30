#include <iostream>
#include <random>
#include <string>
#include "karger.h"

void runExperiment(
    const std::string &name,
    const Graph &graph,
    int trueMinCut,
    int trials,
    std::mt19937 &rng)
{
    int successes = 0;

    for (int i = 0; i < trials; ++i)
    {
        int cut = kargerMinCut(graph, rng);

        if (cut == trueMinCut)
        {
            ++successes;
        }
    }

    double successRate =
        static_cast<double>(successes) / trials;

    double theoreticalBound =
        2.0 / (graph.n * (graph.n - 1));

    std::cout
        << name << ","
        << graph.n << ","
        << graph.edges.size() << ","
        << trials << ","
        << successes << ","
        << successRate << ","
        << theoreticalBound
        << '\n';
}

int main()
{
    std::mt19937 rng(12345);

    int trials = 5000;

    std::cout
        << "graph,n,m,trials,successes,success_rate,theoretical_bound\n";

    for (int n = 4; n <= 12; n += 2)
    {
        Graph cycle = makeCycle(n);
        runExperiment("cycle", cycle, 2, trials, rng);

        Graph complete = makeCompleteGraph(n);
        runExperiment("complete", complete, n - 1, trials, rng);
    }

    return 0;
}