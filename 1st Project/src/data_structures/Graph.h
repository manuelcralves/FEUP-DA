#ifndef G16_3_GRAPH_H
#define G16_3_GRAPH_H
#include <map>
#include <cmath>
#include <chrono>
#include <cfloat>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <list>
#include <unordered_map>
#include <algorithm>
#include "VertexEdge.h"

class Graph {
public:
    /**
     * @brief Graph class destructor.
     *
     * The destructor for the Graph class is responsible for deallocating the dynamically allocated memory
     * for the distance matrix and path matrix, which are used in graph algorithms.
     * It calls the helper functions 'deleteMatrix()' to delete the memory for both matrices.
     */
    ~Graph();

    /**
     * @brief Finds a vertex in the graph by name.
     *
     * @param name The name of the vertex to be found.
     * @return A pointer to the vertex if found, nullptr otherwise.
     */
    Vertex *findVertex(const std::string &name) const;

    /**
     * @brief Adds a vertex to the graph.
     *
     * @param vertex A pointer to the vertex to be added.
     * @return true if the vertex was added successfully, false otherwise.
     */
    bool addVertex(Vertex *vertex);

    /**
     * @brief Adds a bidirectional edge between two vertices in the graph.
     *
     * @param v1 Pointer to the first vertex.
     * @param v2 Pointer to the second vertex.
     * @param w Weight of the edge.
     * @param service Service associated with the edge.
     * @return true if the edge was added successfully, false otherwise.
     */
    bool addBidirectionalEdge(Vertex *v1, Vertex *v2, double w, std::string service);

    /**
     * @brief Implements the Edmonds-Karp algorithm to compute the maximum flow in the graph from a source vertex to a target vertex.
     *
     * The function implements the Edmonds-Karp algorithm to compute the maximum flow in the graph from a source vertex to a target vertex.
     * It takes two Vertex pointers, representing the source and target vertices, as input. It uses a lambda function for Breadth-First Search (BFS)
     * to find augmenting paths from the source to the target. The lambda function performs the BFS and updates the flow of the edges in the augmenting path.
     * The function maintains a running total of the maximum flow and returns it as the result.
     *
     * @param s The source vertex.
     * @param t The target vertex.
     * @return The maximum flow from the source to the target vertex.
     * Time Complexity: O(VE^2)
     */
    double EdmondsKarp(Vertex* s,Vertex* t);

    /**
     * @brief Computes the maximum flow between pairs of vertices in the graph using the Edmonds-Karp algorithm.
     *
     * The function finds the maximum flow between pairs of vertices in the graph using the Edmonds-Karp algorithm.
     * It iterates over all pairs of vertices in the graph, computes the maximum flow between each pair using the
     * Edmonds-Karp algorithm, and keeps track of the pairs with the maximum flow. The result is printed to the standard
     * output along with the execution time in milliseconds.
     */
    void MaxFlowBetweenPairs();

    /**
     * @brief Computes the top districts with the highest maximum flow between pairs of vertices in the graph using the Edmonds-Karp algorithm.
     *
     * The function computes the top districts with the highest maximum flow between pairs of vertices in the graph using the Edmonds-Karp algorithm.
     * It iterates over all pairs of vertices in the graph, computes the maximum flow between each pair using the Edmonds-Karp algorithm,
     * and accumulates the maximum flow for each district. Then, it sorts the districts based on their accumulated maximum flow in descending order
     * and prints the top districts along with their accumulated maximum flow to the standard output.
     *
     * @param k The number of top districts to print.
     */
    void topDistricts(int k);

    /**
     * @brief Computes the top municipalities with the highest maximum flow between pairs of vertices in the graph using the Edmonds-Karp algorithm.
     *
     * The function computes the top municipalities with the highest maximum flow between pairs of vertices in the graph using the Edmonds-Karp algorithm.
     * It iterates over all pairs of vertices in the graph, computes the maximum flow between each pair using the Edmonds-Karp algorithm,
     * and accumulates the maximum flow for each municipality. Then, it sorts the municipalities based on their accumulated maximum flow in descending order
     * and prints the top municipalities along with their accumulated maximum flow to the standard output.
     *
     * @param k The number of top municipalities to print.
     */
    void topMunicipalities(int k);

    /**
     * @brief Computes the maximum number of trains that can simultaneously arrive at a given station in the graph using the Edmonds-Karp algorithm.
     *
     * The function computes the maximum number of trains that can simultaneously arrive at a given station in the graph using the Edmonds-Karp algorithm.
     * It adds a source vertex to the graph and connects it to all adjacent vertices of the given station. Then, it runs the Edmonds-Karp algorithm
     * to compute the maximum flow from the source vertex to the given station, which represents the maximum number of trains that can simultaneously arrive at the station.
     * Finally, it removes the source vertex and the edges added to the graph.
     *
     * @param station The station vertex for which to compute the maximum number of trains that can simultaneously arrive.
     * Time Complexity: O(E^2 V)
     */
    void maxTrainsAtStation(Vertex *station);
    /**
     * @brief Gets the vector of vertices in the graph.
     *
     * @return A vector containing pointers to all the vertices in the graph.
     */
    std::vector<Vertex *> getVertexSet() const;

    /**
     * @brief Removes a vertex from the graph by station name.
     *
     * @param station_name The name of the vertex (station) to be removed.
     * @return True if the vertex was successfully removed, false otherwise.
     */
    bool removeVertex(const std::string& station_name);

    /**
     * @brief Computes the most affected stations in the graph by comparing the maximum flow with another graph.
     *
     * The function computes the most affected stations in the graph by comparing the maximum flow of each edge in the graph with another graph.
     * It takes a Graph object 'rc' as input, which represents another graph for comparison.
     * The function iterates over all vertices and their adjacent edges in the graph and computes the maximum flow using the Edmonds-Karp algorithm
     * for each edge. It then compares the maximum flow of the edge in the original graph with the corresponding edge in 'rc' graph.
     * If the maximum flows are different, the function calculates the absolute difference and keeps track of the maximum difference found so far.
     * It also maintains a set of added station pairs to avoid duplicates. The function returns a vector of strings representing the most affected stations.
     *
     * @param rc The graph to compare with for computing most affected stations.
     * @return A vector of strings representing the most affected stations.
     * Time Complexity: O(V^2 E^2)
     */
    std::vector<std::string> MostAffectStations(Graph rc);
protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    double ** distMatrix = nullptr;
    int **pathMatrix = nullptr;
};

/**
 * @brief Deletes a dynamically allocated 2D integer matrix.
 *
 * This function is responsible for deleting a dynamically allocated 2D integer matrix.
 * It takes a pointer to the matrix 'm' and the number of rows/columns 'n' as input.
 * The function iterates over each row and deletes the dynamically allocated memory for each row,
 * and then deletes the memory allocated for the matrix itself.
 *
 * @param m Pointer to the 2D integer matrix to be deleted.
 * @param n Number of rows/columns in the matrix.
 */
void deleteMatrix(int **m, int n);

/**
 * @brief Deletes a dynamically allocated 2D double matrix.
 *
 * This function is responsible for deleting a dynamically allocated 2D double matrix.
 * It takes a pointer to the matrix 'm' and the number of rows/columns 'n' as input.
 * The function iterates over each row and deletes the dynamically allocated memory for each row,
 * and then deletes the memory allocated for the matrix itself.
 *
 * @param m Pointer to the 2D double matrix to be deleted.
 * @param n Number of rows/columns in the matrix.
 */
void deleteMatrix(double **m, int n);


#endif //G16_3_GRAPH_H

