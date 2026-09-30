#pragma once

#include <vector>
#include <random>

struct Edge
{
    int u;
    int v;
};

struct Graph
{
    int n;
    std::vector<Edge> edges;
};

int kargerMinCut(const Graph &graph, std::mt19937 &rng);
int exactMinCut(const Graph &graph);

Graph makeCycle(int n);
Graph makeCompleteGraph(int n);
Graph makeTwoClusterGraph(int clusterSize, int bridgeEdges);