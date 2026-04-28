#include "Graph.h"
#include "GraphIO.h"
#include "PrimMST.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <exception>

void printMSTToConsole(
    const std::string& title,
    const std::vector<Edge>& edgeOrder,
    const Graph& mstGraph)
{
    std::cout << title << std::endl;

    for (const Edge& edge : edgeOrder)
    {
        edge.print(std::cout);
    }

    mstGraph.print(std::cout);

    std::cout << "End of " << title.substr(6) << std::endl;
    std::cout << std::endl;
}

int main()
{
    try
    {
        const std::string inputFileName = "InitialGraph.txt";

        std::shared_ptr<Graph> initialGraph = GraphIO::readGraphFromFile(inputFileName);
        std::cout << "Initial Graph" << std::endl;
        initialGraph->print(std::cout);
        std::cout << "End of initial graph" << std::endl;
        std::cout << std::endl;

        std::vector<int> startingVertices = { 3, 7, 9 };

        for (int i = 0; i < static_cast<int>(startingVertices.size()); i++)
        {
            int startVertex = startingVertices[i];

            MSTResult result = PrimMST::build(*initialGraph, startVertex);

            std::string title = "Begin MST " + std::to_string(i + 1) + " starting at Vertex " + std::to_string(startVertex);
            std::string outputFileName = "MST" + std::to_string(i + 1) + "_StartVertex" + std::to_string(startVertex) + ".txt";

            printMSTToConsole(title, result.edgeOrder, *result.mstGraph);

            GraphIO::writeMSTToFile(outputFileName, title, result.edgeOrder, *result.mstGraph);
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Program error: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}