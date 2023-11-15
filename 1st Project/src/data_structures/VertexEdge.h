#ifndef G16_3_VERTEXEDGE_H
#define G16_3_VERTEXEDGE_H
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

class Edge;

#define INF std::numeric_limits<double>::max()


/************************* Vertex  **************************/

class Vertex {
public:
    /**
     * @brief Constructor for Vertex class.
     *
     * @param name The name of the vertex.
     */
    Vertex(std::string name);

    /**
     * @brief Constructor for Vertex class.
     *
     * @param name The name of the vertex.
     * @param district The district of the vertex.
     * @param municipality The municipality of the vertex.
     * @param township The township of the vertex.
     * @param line The line of the vertex.
     */
    Vertex(std::string name,std::string district,std::string municipality,std::string township,std::string line);

    /**
     * @brief Overloaded less-than operator for comparing vertices based on their 'dist' member variable.
     *
     * @param vertex The vertex to be compared.
     *
     * @return true if the current vertex's 'dist' is less than the 'dist' of the input vertex, false otherwise.
     */
    bool operator<(Vertex & vertex) const;

    /**
     * @brief Gets the name of the vertex.
     *
     * @return The name of the vertex.
     */
    std::string getName() const;

    /**
     * @brief Gets the district of the vertex.
     *
     * @return The district of the vertex.
     */
    std::string getDistrict() const;

    /**
     * @brief Gets the municipality of the vertex.
     *
     * @return The municipality of the vertex.
     */
    std::string getMunicipality() const;


    /**
     * @brief Gets the adjacency list of the vertex.
     *
     * @return A vector of pointers to edges representing the adjacency list of the vertex.
     */
    std::vector<Edge *> getAdj() const;

    /**
     * @brief Checks if the vertex has been visited.
     *
     * @return true if the vertex has been visited, false otherwise.
     */
    bool isVisited() const;
    /**
     * @brief Gets the path associated with the vertex.
     *
     * @return A pointer to the edge representing the path associated with the vertex.
     */
    Edge *getPath() const;

    /**
     * @brief Sets the visited status of the vertex.
     *
     * @param visited The visited status to be set.
     */
    void setVisited(bool visited);

    /**
     * @brief Sets the path associated with the vertex.
     *
     * @param path A pointer to the edge representing the path to be set.
     */
    void setPath(Edge *path);
    /**
     * @brief Adds an edge from the current vertex to a destination vertex with a given weight and service.
     *
     * @param d Pointer to the destination vertex.
     * @param w Weight of the edge.
     * @param service The service associated with the edge.
     *
     * @return Pointer to the newly created edge.
     */
    Edge * addEdge(Vertex *dest, double w,std::string service);

    /**
     * @brief Adds an edge from the current vertex to a destination vertex with a given weight and service.
     *
     * @param d Pointer to the destination vertex.
     * @param w Weight of the edge.
     * @param service The service associated with the edge.
     *
     * @return Pointer to the newly created edge.
     */
    bool removeEdge(std::string destName);
protected:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;
    std::vector<Edge *> adj;
    bool visited = false;
    bool processing = false;
    unsigned int indegree;
    double dist = 0;
    Edge *path = nullptr;
    std::vector<Edge *> incoming;
};

/********************** Edge  ****************************/

class Edge {
public:
    /**
     * @brief Constructor for Edge class.
     *
     * @param orig Pointer to the origin vertex of the edge.
     * @param dest Pointer to the destination vertex of the edge.
     * @param w Weight of the edge.
     * @param service The service associated with the edge.
     */
    Edge(Vertex *orig, Vertex *dest, double w,std::string service);

    /**
     * @brief Gets the destination vertex of the edge.
     *
     * @return Pointer to the destination vertex of the edge.
     */
    Vertex * getDest() const;

    /**
     * @brief Gets the weight of the edge.
     *
     * @return The weight of the edge.
     */
    double getWeight() const;

    /**
     * @brief Gets the service associated with the edge.
     *
     * @return The service associated with the edge.
     */
    std::string getService() const;

    /**
     * @brief Gets the origin vertex of the edge.
     *
     * @return Pointer to the origin vertex of the edge.
     */
    Vertex * getOrig() const;

    /**
     * @brief Gets the reverse edge associated with this edge.
     *
     * @return Pointer to the reverse edge associated with this edge.
     */
    Edge *getReverse() const;

    /**
     * @brief Gets the flow of the edge.
     *
     * @return The flow of the edge.
     */
    double getFlow() const;

    /**
     * @brief Sets the reverse edge associated with this edge.
     *
     * @param reverse Pointer to the reverse edge to be set.
     */
    void setReverse(Edge *reverse);

    /**
     * @brief Sets the flow of the edge.
     *
     * @param flow The flow to be set.
     */
    void setFlow(double flow);
protected:
    Vertex * dest;
    double weight;
    std::string service;
    Vertex *orig;
    Edge *reverse = nullptr;
    double flow = 0;
};

#endif //G16_3_VERTEXEDGE_H
