# [kd-tree](https://en.wikipedia.org/wiki/K-d_tree)
---
In computer science, a k-dimensional tree is a space-partitioning data structure for organizing points in a k-dimensional space. In machine learning, we sometimes have to find the nearest neighbor for a given point. This can be efficiently done using k-d trees. k-d trees are a special case of binary space partitioning trees.


## Idea
`nearestPointInSubtree` function calls itself recursively. It also handles the edge cases (e.g. one child node).
This is done as follows:
1. Figure out on which side of the separating hyperplane the query point lies and recursively descends into that part of the tree.
2. If the distance of the query point to the best point in that sub-tree is smaller than the distance to the separating hyperplane (`axisDistToRoot`), just return the best point and corresponding distance from that sub-tree.
3. Otherwise the closest point to the query point can also be the root node or a point in the other sub-tree. Calculate all distances and return the node with the smallest distance to the query point.

## Compile

    `g++ -std=c++17 kdtree.cpp -o kdtree.out`
or

    `make`
