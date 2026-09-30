#include <iostream>
#include <random>
#include "karger.h"

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

    std::random_device rd;
    std::mt19937 rng(rd());

    int trials = 1000;
    int successes = 0;

    for (int i = 0; i < trials; ++i)
    {
        int cut = kargerMinCut(graph, rng);

        if (cut == 2)
        {
            ++successes;
        }
    }

    double successRate =
        static_cast<double>(successes) / trials;

    double theoreticalBound =
        2.0 / (graph.n * (graph.n - 1));

    std::cout << "Trials: " << trials << '\n';
    std::cout << "Successes: " << successes << '\n';
    std::cout << "Success rate: " << successRate << '\n';
    std::cout << "Theoretical lower bound: "
              << theoreticalBound << '\n';

    return 0;
}