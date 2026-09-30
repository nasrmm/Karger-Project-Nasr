#include <iostream>
#include "karger.h"
#include <random>

int cut = kargerMinCut(graph, rng);

int main()
{
    Graph graph;

    graph.n = 6;
    graph.edges = {
        {0, 1},
        {1, 2},
        {2, 0},

        {3, 4},
        {4, 5},
        {5, 3},

        {2, 5},
        {1, 4}};

    int trials = 1000;
    int successes = 0;

    for (int i = 0; i < trials; ++i)
    {
        int cut = kargerMinCut(graph);

        if (cut == 2)
        {
            ++successes;
        }
    }

    double successRate =
        static_cast<double>(successes) / trials;

    std::cout << "Trials: " << trials << '\n';
    std::cout << "Successes: " << successes << '\n';
    std::cout << "Success rate: " << successRate << '\n';

    return 0;
}