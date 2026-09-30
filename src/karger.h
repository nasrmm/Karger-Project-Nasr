#pragma once

#include <random>

int kargerMinCut(const Graph &graph, std::mt19937 &rng);

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

int kargerMinCut(const Graph &graph);