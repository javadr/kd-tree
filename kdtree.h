#ifndef __KDTREE_HEADER__
#define __KDTREE_HEADER__

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>

#define red     "\033[0;31m"
#define blue    "\033[0;34m"
#define green   "\033[0;32m"
#define grey    "\033[0;37m"
#define reset   "\033[0m"

constexpr int pointDims = 3;
typedef std::array<float, pointDims> Point;

std::ostream& operator<<(std::ostream& s, Point const& point);
void printPoint(Point &point);

struct Node {
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Point point;

    Node(Point &pt) : left(nullptr), right(nullptr), point(pt) { }
};

class KDTree {
public:
    KDTree(std::vector<Point> &points) {
        root_ = constructTree(points, 0);
    }

    Point nearestNeighbour(Point queryPoint) const {
        auto [node, dist] = nearestPointInSubtree(queryPoint, root_, 0);
        return node->point;
    }

private:
    std::shared_ptr<Node> constructTree(std::vector<Point> &points, int depth) {
        if (points.size() == 0) {
            return nullptr;
        }

        int axis = depth % pointDims;
        std::sort(points.begin(), points.end(),
                  [&] (const Point &a, const Point &b) {
                      return a[axis] < b[axis];
                });
        int medianIdx = points.size() / 2;
        auto node = std::make_shared<Node>(points[medianIdx]);
        std::vector<Point> leftPts(medianIdx);
        std::copy(points.begin(), points.begin() + medianIdx, leftPts.begin());
        std::vector<Point> rightPts(points.size() - medianIdx - 1);
        std::copy(points.begin() + medianIdx + 1, points.end(), rightPts.begin());
        node->left = constructTree(leftPts, depth + 1);
        node->right = constructTree(rightPts, depth + 1);
        return node;
    }

    float distance(Point p1, Point p2) const{
        float distToRoot = 0.0;
        for (int i = 0; i < pointDims; ++i) {
            distToRoot += std::pow(p1[i] - p2[i], 2.0);
        }
        return std::pow(distToRoot, 0.5);
    }

    std::shared_ptr<Node> closer(Point queryPoint,
                            std::shared_ptr<Node> next, std::shared_ptr<Node> oppose) const{
        if (!next) return oppose;
        if (!oppose) return next;

        float d1 = distance(queryPoint, next->point);
        float d2 = distance(queryPoint, oppose->point);

        if (d1 < d2)
            return next;
        else
            return oppose;
    }

    std::tuple<std::shared_ptr<Node>, float> nearestPointInSubtree(
        Point queryPoint, std::shared_ptr<Node> rootNode, int depth) const {

        if (!rootNode) return {nullptr, 0};

        //std::cout << "depth: " << depth << " " << rootNode->point;

        int axis = depth % pointDims;
        float axisDistToRoot = queryPoint[axis] - rootNode->point[axis];
        float distToRoot = 0.0;
        for (int i = 0; i < pointDims; ++i) {
            distToRoot += std::pow(queryPoint[i] - rootNode->point[i], 2.0);
        }
        distToRoot = std::pow(distToRoot, 0.5);

        if (!rootNode->left && !rootNode->right) {
            return {rootNode, distToRoot};
        }

        std::shared_ptr<Node> next;
        std::shared_ptr<Node> oppose;

        if (queryPoint[axis] > rootNode->point[axis]){
            next = rootNode->right;
            oppose = rootNode->left;
        }
        else{
            next = rootNode->left;
            oppose = rootNode->right;
        }

        auto node = std::get<0>(nearestPointInSubtree(queryPoint, next, depth+1));
        auto bestNode = closer(queryPoint, node, rootNode);
        if ( distance(bestNode->point, queryPoint) > (axisDistToRoot) ){
            node = std::get<0>(nearestPointInSubtree(queryPoint, oppose, depth+1));
            bestNode = closer(queryPoint, node, bestNode);
        }

        return {bestNode, distance(queryPoint, bestNode->point)};
    }

    std::shared_ptr<Node> root_;
};

void printPoint(Point &point) {
    std::cout << "(";
    for (int i = 0; i < pointDims; ++i) {
        std::cout << point[i];
        if (i + 1 < pointDims) {
            std::cout << ", ";
        }
    }
    std::cout << ")" << std::endl << std::endl;
};

std::ostream& operator<<(std::ostream& s, Point const& point){
    std::cout << red << "(" << green;
    for (const auto& i:point) std::cout << std::setprecision(4) << i << red << ", " << green;
    std::cout << red << "\b\b)" << reset << std::endl << std::endl;
    return s;
}

#endif //__KDTREE_HEADER__