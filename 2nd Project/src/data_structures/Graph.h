// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <stack>
#include "../data_structures/MutablePriorityQueue.h"

#include "VertexEdge.h"

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(const int &id) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const int &id,const double &lon,const double &lat);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, double w) const;
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w) const;
    void backtrack(int currentVertex,std::vector<int> &currentPath,double currentCost);
    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;
    std::vector<int> getBestPath() const;
    double getBestCost() const;
    static void dfs(int currentVertex, const std::vector<int> &parent, std::vector<bool> &visited, std::stack<int> &vertexStack, std::vector<int> &route);
    std::vector<std::pair<int, int>> findMinimumSpanningTree(std::vector<int>& parent);
    bool areVerticesConnected(int vertex1, int vertex2);
    double calculateTotalDistance(const std::vector<int> &route);
    double triangularApproximation();
    void nearestNeighbor(Graph &graph);
    void tabuSearch(Graph& graph, int maxIterations, int tabuListSize, int maxIterationsWithoutImprovement);
    bool isTabuAspirational(const std::vector<int>& solution, const std::deque<std::vector<int>>& tabuList, const double diversificationThreshold);
    bool isTabu(const std::vector<int>& solution, const std::deque<std::vector<int>>& tabuList);
    std::vector<int> generateRandomSolution();
    std::vector<int> generateNeighborSolution(const std::vector<int>& solution);
    void simulatedAnnealing(Graph& graph, int maxIterations, double initialTemperature, double coolingRate);
    double acceptanceProbability(double currentCost, double candidateCost, double temperature);
    std::vector<std::vector<int>> generateNeighbors(const std::vector<int>& solution);
    double evaluateSolution(Graph& graph, const std::vector<int>& solution);
    Graph constructMST(Graph& graph);
    std::vector<Vertex*> findVerticesWithOddDegrees(const Graph& mstGraph);
    Graph findMinimumWeightMatching(const Graph& graph, const std::vector<Vertex*>& oddDegreeVertices);
    Graph combineGraphs(const Graph& mstGraph, const Graph& matchingGraph);
    std::vector<int> findEulerianCircuit(Graph& multigraph);
    std::vector<int> removeDuplicates(const std::vector<int>& eulerianCircuit);
    double getEdgeWeight(int source, int destination) const;
    void christofidesAlgorithm(Graph &graph);
    std::vector<Vertex *> MST();
protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    std::vector<int> bestPath;
    double bestCost = std::numeric_limits<double>::max();

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const int &id) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */
