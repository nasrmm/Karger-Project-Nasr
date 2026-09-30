#include <iostream>
#include <random>
#include <string>
#include <chrono>

#include "karger.h"

void runExperiment(
    const std::string &name,
    const Graph &graph,
    int trials,
    std::mt19937 &rng)
{
    // baseline
    auto exactStart =
        std::chrono::high_resolution_clock::now();

    int trueMinCut = exactMinCut(graph);

    auto exactEnd =
        std::chrono::high_resolution_clock::now();

    double exactTimeMs =
        std::chrono::duration<double, std::milli>(
            exactEnd - exactStart)
            .count();

    // Run Karger's randomised algorithm multple times
    int successes = 0;

    auto kargerStart =
        std::chrono::high_resolution_clock::now();

    for (int i = 0; i < trials; ++i)
    {
        int cut = kargerMinCut(graph, rng);

        if (cut == trueMinCut)
        {
            ++successes;
        }
    }

    auto kargerEnd =
        std::chrono::high_resolution_clock::now();

    double kargerTimeMs =
        std::chrono::duration<double, std::milli>(
            kargerEnd - kargerStart)
            .count();

    double successRate =
        static_cast<double>(successes) / trials;

    double theoreticalBound =
        2.0 / (graph.n * (graph.n - 1));

    std::cout
        << name << ","
        << graph.n << ","
        << graph.edges.size() << ","
        << trials << ","
        << trueMinCut << ","
        << successes << ","
        << successRate << ","
        << theoreticalBound << ","
        << kargerTimeMs << ","
        << exactTimeMs
        << '\n';
}

int main()
{
    // Fixed seed makes expeiments reproducible
    std::mt19937 rng(12345);

    const int trials = 5000;

    std::cout
        << "graph,"
        << "n,"
        << "m,"
        << "trials,"
        << "min_cut,"
        << "successes,"
        << "success_rate,"
        << "theoretical_bound,"
        << "karger_time_ms,"
        << "exact_time_ms"
        << '\n';

    for (int n = 4; n <= 12; n += 2)
    {
        Graph cycle = makeCycle(n);

        runExperiment(
            "cycle",
            cycle,
            trials,
            rng);

        Graph complete =
            makeCompleteGraph(n);

        runExperiment(
            "complete",
            complete,
            trials,
            rng);

        // Avoid 4 vertex case
        if (n >= 6)
        {
            Graph clusters =
                makeTwoClusterGraph(
                    n / 2,
                    2);

            runExperiment(
                "two_cluster",
                clusters,
                trials,
                rng);
        }
    }

    return 0;
}