#include "kdtree.h"

int main() {
    // Insert some points to the tree
    std::vector<Point> points {
        {0.935, 0.086, 0.069},
        {0.407, 0.5  , 0.349},
        {0.959, 0.394, 0.004},
        {0.418, 0.608, 0.452},
        {0.331, 0.704, 0.418},
        {0.76 , 0.988, 0.544},
        {0.89 , 0.063, 0.137},
        {0.574, 0.903, 0.101},
        {0.9  , 0.889, 0.708},
        {0.322, 0.963, 0.816}
    };
    KDTree tree(points);

    // Find nearest neighbour to a given point
    Point nn = tree.nearestNeighbour({0.5, 0.5, 0.5});
    std::cout << "I found the following nearest neighbour for (0.5, 0.5, 0.5),"
              << std::endl << "[expected (0.418, 0.608, 0.452)]:" << std::endl
              << nn;
    //printPoint(nn);

    nn = tree.nearestNeighbour({0.2, 0.7, 0.8});
    std::cout << "I found the following nearest neighbour for (0.2, 0.7, 0.8),"
              << std::endl << " [expected (0.322, 0.963, 0.816)]:" << std::endl
              << nn;
    //printPoint(nn);

    nn = tree.nearestNeighbour({0.7, 0.2, 0.5});
    std::cout << "I found the following nearest neighbour for (0.7, 0.2, 0.5),"
              << std::endl << " [expected (0.89 , 0.063, 0.137)]:" << std::endl
              << nn;
    //printPoint(nn);

    return 0;
}
