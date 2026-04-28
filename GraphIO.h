#ifndef GRAPH_IO_H
#define GRAPH_IO_H

#include "Graph.h"
#include "Edge.h"

#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>

class GraphIO
{
public:
    static std::shared_ptr<Graph> readGraphFromFile(const std::string& fileName)
    {
        std::ifstream inputFile(fileName);

        if (!inputFile)
        {
            throw std::runtime_error("Could not open input file: " + fileName);
        }
        int vertices = 0;
        inputFile >> vertices;

        if (vertices <= 0)
        {
            throw std::runtime_error("Invalid vertex count in file: " + fileName);
        }

        std::shared_ptr<Graph> graph = std::make_shared<Graph>(vertices);

        for (int row = 0; row < vertices; row++)
        {
            for (int col = 0; col < vertices; col++)
            {
                int weight = 0;
                inputFile >> weight;
                if (!inputFile)
                {
                    throw std::runtime_error("Invalid matrix data in file: " + fileName);
                }
                graph->setWeight(row, col, weight);
            }
        }

        return graph;
    }

    static void writeMSTToFile(
        const std::string& fileName,
        const std::string& mstTitle,
        const std::vector<Edge>& edgeOrder,
        const Graph& mstGraph)
    {
        std::ofstream outputFile(fileName);

        if (!outputFile)
        {
            throw std::runtime_error("Could not open output file: " + fileName);
        }

        outputFile << mstTitle << std::endl;

        for (const Edge& edge : edgeOrder)
        {
            edge.print(outputFile);
        }

        mstGraph.print(outputFile);

        outputFile << "End of " << mstTitle.substr(6) << std::endl;
    }
};

#endif