#include "karger.h"
#include "dsu.h"

#include <random>
#include <vector>
#include <limits>

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

Graph makeTwoClusterGraph(int clusterSize, int bridgeEdges)
{
    Graph graph;
    graph.n = clusterSize * 2;

    // complete graph on first cluster
    for (int u = 0; u < clusterSize; ++u)
    {
        for (int v = u + 1; v < clusterSize; ++v)
        {
            graph.edges.push_back({u, v});
        }
    }

    // Complete graph on secoond cluster
    for (int u = clusterSize; u < 2 * clusterSize; ++u)
    {
        for (int v = u + 1; v < 2 * clusterSize; ++v)
        {
            graph.edges.push_back({u, v});
        }
    }

    // Bridhes between clusters
    for (int i = 0; i < bridgeEdges; ++i)
    {
        graph.edges.push_back({i % clusterSize,
                               clusterSize + (i % clusterSize)});
    }

    return graph;
}

int exactMinCut(const Graph &graph)
{
    int best = std::numeric_limits<int>::max();

    // vertex 0 on one fixed side
    int combinations = 1 << (graph.n - 1);

    for (int mask = 1; mask < combinations; ++mask)
    {
        int cutSize = 0;

        for (const Edge &edge : graph.edges)
        {
            bool sideU;
            bool sideV;

            if (edge.u == 0)
            {
                sideU = false;
            }
            else
            {
                sideU = (mask >> (edge.u - 1)) & 1;
            }

            if (edge.v == 0)
            {
                sideV = false;
            }
            else
            {
                sideV = (mask >> (edge.v - 1)) & 1;
            }

            if (sideU != sideV)
            {
                ++cutSize;
            }
        }

        if (cutSize < best)
        {
            best = cutSize;
        }
    }

    return best;
}