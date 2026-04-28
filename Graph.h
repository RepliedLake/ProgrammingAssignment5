#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>

class Graph
{
private:
    int vertexCount;
    std::unique_ptr<std::vector<std::vector<int>>> matrix;

public:
    Graph() : vertexCount(0), matrix(std::make_unique<std::vector<std::vector<int>>>())
    {}
    explicit Graph(int vertices) : vertexCount(vertices), matrix(std::make_unique<std::vector<std::vector<int>>>(vertices, std::vector<int>(vertices, 0)))
    {}
    int vertices() const
    {
        return vertexCount;
    }
    int getWeight(int row, int col) const
    {
        return (*matrix)[row][col];
    }
    void setWeight(int row, int col, int weight)
    {
        (*matrix)[row][col] = weight;
    }
    void addUndirectedEdge(int from, int to, int weight)
    {
        (*matrix)[from][to] = weight;
        (*matrix)[to][from] = weight;
    }
    int edgeCount() const
    {
        int count = 0;
        for (int row = 0; row < vertexCount; row++)
        {
            for (int col = row + 1; col < vertexCount; col++)
            {
                if ((*matrix)[row][col] != 0)
                {
                    count++;
                }
            }
        }
        return count;
    }
    void print(std::ostream& out) const
    {
        out << "Number of vertices is " << vertexCount << std::endl;
        out << "Number of edges is " << edgeCount() << std::endl;
        out << "Matrix is:" << std::endl;

        for (int row = 0; row < vertexCount; row++)
        {
            for (int col = 0; col < vertexCount; col++)
            {
                out << (*matrix)[row][col];
                if (col < vertexCount - 1)
                {
                    out << " ";
                }
            }
            out << std::endl;
        }
    }
};

#endif