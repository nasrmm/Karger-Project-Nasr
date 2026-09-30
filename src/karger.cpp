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

Graph makeCycle(int n)
{
    Graph graph;
    graph.n = n;

    for (int i = 0; i < n; ++i)
    {
        graph.edges.push_back({i, (i + 1) % n});
    }

    return graph;
}

Graph makeCompleteGraph(int n)
{
    Graph graph;
    graph.n = n;

    for (int u = 0; u < n; ++u)
    {
        for (int v = u + 1; v < n; ++v)
        {
            graph.edges.push_back({u, v});
        }
    }

    return graph;
}