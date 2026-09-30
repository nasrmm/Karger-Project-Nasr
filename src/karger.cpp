#include "karger.h"
#include "dsu.h"

#include <random>
#include <vector>

int kargerMinCut(const Graph &graph, std::mt19937 &rng)
{
    DSU dsu(graph.n);
    int components = graph.n;

    while (components > 2)
    {
        std::vector<Edge> survivingEdges;

        for (const Edge &edge : graph.edges)
        {
            if (dsu.find(edge.u) != dsu.find(edge.v))
            {
                survivingEdges.push_back(edge);
            }
        }

        std::uniform_int_distribution<int> dist(
            0,
            static_cast<int>(survivingEdges.size()) - 1);

        Edge chosen = survivingEdges[dist(rng)];

        dsu.unite(chosen.u, chosen.v);
        --components;
    }

    int cutSize = 0;

    for (const Edge &edge : graph.edges)
    {
        if (dsu.find(edge.u) != dsu.find(edge.v))
        {
            ++cutSize;
        }
    }

    return cutSize;
}