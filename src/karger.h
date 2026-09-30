#pragma once

#include <vector>

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