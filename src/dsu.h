#pragma once

#include <vector>
#include <utility>

class DSU
{
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DSU(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);

        if (a == b)
        {
            return false;
        }

        if (rank[a] < rank[b])
        {
            std::swap(a, b);
        }

        parent[b] = a;

        if (rank[a] == rank[b])
        {
            ++rank[a];
        }

        return true;
    }
};