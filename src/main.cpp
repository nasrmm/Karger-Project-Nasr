#include <iostream>
#include "karger.h"

int main()
{
    Graph triangle;

    triangle.n = 3;
    triangle.edges = {
        {0, 1},
        {1, 2},
        {2, 0}};

    std::cout << "Karger min cut: "
              << kargerMinCut(triangle)
              << '\n';

    return 0;
}