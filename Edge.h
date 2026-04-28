#ifndef EDGE_H
#define EDGE_H

#include <iostream>

class Edge
{
private:
    int fromVertex;
    int toVertex;
    int edgeWeight;

public:
    Edge() : fromVertex(0), toVertex(0), edgeWeight(0)
    {}

    Edge(int from, int to, int weight) : fromVertex(from), toVertex(to), edgeWeight(weight)
    {}

    int from() const
    {
        return fromVertex;
    }

    int to() const
    {
        return toVertex;
    }

    int weight() const
    {
        return edgeWeight;
    }

    void print(std::ostream& out) const
    {
        out << "Add edge " << fromVertex << " to " << toVertex << " Weight: " << edgeWeight << std::endl;
    }
};

#endif