#include <iostream>
#include "karger.h"
#include "dsu.h"

int main()
{
    Graph triangle;

    triangle.n = 3;
    triangle.edges = {
        {0, 1},
        {1, 2},
        {2, 0}};

    std::cout << "Vertices: " << triangle.n << '\n';
    std::cout << "Edges: " << triangle.edges.size() << '\n';

    return 0;
}