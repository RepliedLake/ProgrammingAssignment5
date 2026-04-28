#ifndef PRIM_MST_H
#define PRIM_MST_H

#include "Graph.h"
#include "Edge.h"

#include <memory>
#include <queue>
#include <vector>
#include <stdexcept>

struct MSTResult
{
    std::shared_ptr<Graph> mstGraph;
    std::vector<Edge> edgeOrder;
};

struct PriorityEdge
{
    int from;
    int to;
    int weight;

    PriorityEdge(int sourceVertex, int destinationVertex, int edgeWeight) : from(sourceVertex), to(destinationVertex), weight(edgeWeight)
    {}
};

struct ComparePriorityEdge
{
    bool operator()(const PriorityEdge& left, const PriorityEdge& right) const
    {
        if (left.weight != right.weight)
        {
            return left.weight > right.weight;
        }

        if (left.from != right.from)
        {
            return left.from > right.from;
        }

        return left.to > right.to;
    }
};

class PrimMST
{
private:
    static void addOutgoingEdges(const Graph& graph, int vertex, const std::vector<bool>& visited, std::priority_queue<PriorityEdge, std::vector<PriorityEdge>, ComparePriorityEdge>& candidateEdges)
    {
        for (int neighbor = 0; neighbor < graph.vertices(); neighbor++)
        {
            int weight = graph.getWeight(vertex, neighbor);
            if (weight != 0 && !visited[neighbor])
            {
                candidateEdges.push(PriorityEdge(vertex, neighbor, weight));
            }
        }
    }

public:
    static MSTResult build(const Graph& graph, int startVertex)
    {
        if (startVertex < 0 || startVertex >= graph.vertices())
        {
            throw std::runtime_error("Invalid starting vertex.");
        }
        std::shared_ptr<Graph> mstGraph = std::make_shared<Graph>(graph.vertices());
        std::vector<Edge> edgeOrder;
        std::vector<bool> visited(graph.vertices(), false);

        std::priority_queue<PriorityEdge, std::vector<PriorityEdge>, ComparePriorityEdge> candidateEdges;
        visited[startVertex] = true;
        addOutgoingEdges(graph, startVertex, visited, candidateEdges);

        while (!candidateEdges.empty() &&
            static_cast<int>(edgeOrder.size()) < graph.vertices() - 1)
        {
            PriorityEdge current = candidateEdges.top();
            candidateEdges.pop();
            if (visited[current.to])
            {
                continue;
            }

            visited[current.to] = true;
            mstGraph->addUndirectedEdge(current.from, current.to, current.weight);
            edgeOrder.push_back(Edge(current.from, current.to, current.weight));
            addOutgoingEdges(graph, current.to, visited, candidateEdges);
        }

        if (static_cast<int>(edgeOrder.size()) != graph.vertices() - 1)
        {
            throw std::runtime_error("Graph is disconnected. MST could not be completed.");
        }
        return MSTResult{ mstGraph, edgeOrder };
    }
};

#endif