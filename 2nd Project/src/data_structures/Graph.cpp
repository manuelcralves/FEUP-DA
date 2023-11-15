// By: Gonçalo Leão

#include <random>
#include <unordered_set>
#include <stack>
#include <iomanip>
#include "Graph.h"


int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}
std::vector<int> Graph::getBestPath() const {
    return bestPath;
}

double Graph::getBestCost() const {
    return bestCost;
}
/*
* Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const int &id) const {
    for (int i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id) {
            return i;
        }
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const int &id,const double &longitude,const double &lat) {
    if (findVertex(id) != nullptr)
        return false;

    auto* newVertex = new Vertex(id, longitude, lat);

    // Find the correct position to insert the new vertex
    auto it = std::upper_bound(vertexSet.begin(), vertexSet.end(), newVertex, [](const Vertex* v1, const Vertex* v2) {
        return v1->getId() < v2->getId();
    });

    vertexSet.insert(it, newVertex);
    return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const int &sourc, const int &dest, double w) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

/**
 * @brief Backtracking algorithm to find the best path in a graph.
 *  This function is recursive and it is used to find the best path using the backtracking algorithm.
 * Starting from a given current vertex, it explores all possible paths by recursively traversing
 * the neighboring vertices. It keeps track of the current path and cost, updating the best path
 * and cost whenever a complete cycle (path) is formed.
 * @param currentVertex The current vertex being visited.
 * @param currentPath The current path being constructed.
 * @param currentCost The current cost of the path.
 * @return void
 * @note The complexity of the backtracking algorithm depends on the size and structure of the graph.
 * In the worst case, where every vertex is connected to every other vertex, the number of possible
 * paths to explore grows factorially with the number of vertices. Therefore, the complexity can be
 * expressed as O((n-1)!), where n is the number of vertices in the graph. It is important to note
 * that the backtracking algorithm can be computationally expensive for large graphs, and alternative
 * algorithms such as dynamic programming or heuristics may be more efficient in those cases.
 */
void Graph::backtrack(int currentVertex, std::vector<int> &currentPath,double currentCost) {
    if (currentPath.size() == getNumVertex() && currentVertex == 0) {

        if (currentCost < bestCost) {
            bestPath = currentPath;
            bestCost = currentCost;
        }
        return;
    }

    Vertex* vertex = findVertex(currentVertex);
    if (vertex == nullptr) {
        return;
    }


    for (const auto& edge : vertex->getAdj()) {
        Vertex* nextVertex = edge->getDest();


        if (std::find(currentPath.begin(), currentPath.end(), nextVertex->getId()) != currentPath.end()) {
            continue;
        }


        currentPath.push_back(nextVertex->getId());
        double newCost = currentCost + edge->getWeight();

        backtrack(nextVertex->getId(), currentPath, newCost);

        currentPath.pop_back();
    }
}

/**
 * @brief Calculates the Haversine distance between two coordinates.
 * This function calculates the Haversine distance between two coordinates on the Earth's surface
 * using their latitude and longitude values. The Haversine formula takes into account the Earth's
 * spherical shape and provides an approximation of the distance between two points.
 * @param lat1 The latitude of the first coordinate.
 * @param lon1 The longitude of the first coordinate.
 * @param lat2 The latitude of the second coordinate.
 * @param lon2 The longitude of the second coordinate.
 * @return The Haversine distance between the two coordinates in meters.
 * @note The Haversine distance is calculated using the Earth's radius of approximately 6,371,000 meters.
 * If all input coordinates are equal to zero (lat1=0, lon1=0, lat2=0, lon2=0), the function returns 0.0,
 * indicating no distance between the coordinates.
 * @note The complexity of this function is constant, O(1), as it performs a fixed number of arithmetic operations.
 * However, it is important to note that this calculation assumes a spherical Earth model and may not be entirely
 * accurate in all cases, especially over long distances or near the poles.
 */
double calculateHaversineDistance(double lat1, double lon1, double lat2, double lon2) {
    const double earthRadius = 6371000.0; // Earth's radius in meters

    if(lat1 == 0 && lon1 == 0 && lat2 == 0 && lon2 == 0){
        return 0.0;
    }

    double lat1Rad = lat1 * M_PI / 180.0;
    double lon1Rad = lon1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double lon2Rad = lon2 * M_PI / 180.0;

    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;

    double a = std::sin(dLat / 2.0) * std::sin(dLat / 2.0) +
               std::cos(lat1Rad) * std::cos(lat2Rad) *
               std::sin(dLon / 2.0) * std::sin(dLon / 2.0);
    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
    double distance = earthRadius * c;

    return distance;
}

/**
 * @brief Find the minimum spanning tree using Prim's algorithm.
 * This function finds the minimum spanning tree (MST) of the graph using Prim's algorithm.
 * It starts from a specified start vertex and iteratively adds the minimum-weight edges
 * that connect the already visited vertices to the newly visited vertices. The function
 * returns a vector of pairs representing the edges of the minimum spanning tree.
 * @param parent A reference to a vector to store the parent indices for each vertex in the MST.
 * The parent vector is updated during the MST construction.
 * @return A vector of pairs representing the edges of the minimum spanning tree.
 * @note This function assumes that the graph is connected, undirected, and weighted.
 * It uses a priority queue to efficiently select the minimum-weight edges.
 * @note The complexity of this function is O(E log V), where E is the number of edges and V is the number of vertices
 * in the graph. Prim's algorithm iterates over all vertices and edges once, and the priority queue operations
 * take O(log V) time.
 */

std::vector<std::pair<int, int>> Graph::findMinimumSpanningTree(std::vector<int>& parent) {

    std::vector<double> weights(vertexSet.size(), std::numeric_limits<double>::max());
    std::vector<bool> visited(vertexSet.size(), false);

    int startVertex = 0;  // Starting vertex for MST

    weights[startVertex] = 0.0;  // Start with the first vertex


    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;
    pq.emplace(0.0, startVertex);

    while (!pq.empty()) {
        int currentVertex = pq.top().second;
        pq.pop();

        if (visited[currentVertex])
            continue;

        visited[currentVertex] = true;

        // Update key and parent index of adjacent vertices
        for (const auto &edge: vertexSet[currentVertex]->getAdj()) {
            int neighborVertex = edge->getDest()->getId();
            double weight = edge->getWeight();

            if (!visited[neighborVertex] && weight < weights[neighborVertex]) {
                parent[neighborVertex] = currentVertex;
                weights[neighborVertex] = weight;
                pq.emplace(weight, neighborVertex);
            }
        }
    }

    std::vector<std::pair<int, int>> minimumSpanningTree;

    for (int i = 1; i < vertexSet.size(); ++i) {
        //fill the mst
        minimumSpanningTree.emplace_back(parent[i], i);
    }

    return minimumSpanningTree;
}


/**
 * @brief Performs a depth-first search (DFS) traversal of the graph.
 * This function performs a depth-first search (DFS) traversal of the graph, starting at the specified vertex.
 * The DFS traversal is implemented iteratively using a stack.
 * @param currentVertex
 * @param parent
 * @param visited
 * @param vertexStack
 * @param route
 */

void Graph::dfs(int currentVertex, const std::vector<int> &parent, std::vector<bool> &visited, std::stack<int> &vertexStack, std::vector<int> &route) {
    visited[currentVertex] = true;
    vertexStack.push(currentVertex);

    while (!vertexStack.empty()) {
        int city = vertexStack.top();
        vertexStack.pop();

        // Process the city or print its order
        route.push_back(city);

        for (int neighbor = 0; neighbor < parent.size(); ++neighbor) {
            if (parent[neighbor] == city && !visited[neighbor]) {
                visited[neighbor] = true;
                vertexStack.push(neighbor);
            }
        }
    }
}

/**
 * @brief Calculates the total distance of a route.
 * This function calculates the total distance of a route.
 * @param route
 * @note complexity: O(n) n is the number of vertices in the graph;
 * @return
 */
double Graph::calculateTotalDistance(const std::vector<int> &route) {
    double totalDistance = 0.0;

    // Calculate the total distance
    for (int i = 0; i < route.size() - 1; ++i) {
        int vertex1 = route[i];
        int vertex2 = route[i + 1];

        if (!areVerticesConnected(vertex1, vertex2)) {
            totalDistance += calculateHaversineDistance(vertexSet[vertex1]->getLat(), vertexSet[vertex1]->getLongi(), vertexSet[vertex2]->getLat(), vertexSet[vertex2]->getLongi());
        }

        for (const auto& edge : vertexSet[vertex1]->getAdj()) {
            if (edge->getDest()->getId() == vertex2) {
                totalDistance += edge->getWeight();
                break;
            }
        }
    }

    // Add final distance to total distance
    int finalVertex = route.back();
    if (!areVerticesConnected(finalVertex, route[0])) {
        totalDistance += calculateHaversineDistance(vertexSet[finalVertex]->getLat(), vertexSet[finalVertex]->getLongi(), vertexSet[route[0]]->getLat(), vertexSet[route[0]]->getLongi());
    }
    else {
        for (const auto& edge : vertexSet[finalVertex]->getAdj()) {
            if (edge->getDest()->getId() == route[0]) {
                totalDistance += edge->getWeight();
                break;
            }
        }
    }

    return totalDistance;
}

/**
 * @brief This function checks if two vertices are connected.
 * @note complexity: O(n) n is the number of edges in the graph;
 * @param vertex1
 * @param vertex2
 * @return
 */
bool Graph::areVerticesConnected(int vertex1, int vertex2) {

    for(const auto& edge : vertexSet[vertex1]->getAdj()){
        if(edge->getDest()->getId() == vertex2){
            return true;
        }
    }

    return false;
}


/**
 * @brief This function calculates the total distance of a route using the triangular approximation algorithm.
 * This function calculates the total distance of a route using the triangular approximation algorithm.
 * @note complexity: O(E log V) E is the number of edges in the graph and V is the number of vertices in the graph;
 * @return
 */
double Graph::triangularApproximation() {
    // Create the MST using Prim's algorithm
    std::vector<int> par(vertexSet.size(), -1);
    findMinimumSpanningTree(par);

    // Perform DFS traversal to obtain the order of visited cities
    std::vector<bool> visited(vertexSet.size(), false);
    std::vector<int> route;
    std::stack<int> vertexStack;
    dfs(0, par, visited, vertexStack, route);

    // Print the order of visited points
    std::cout << "Order of visited points: ";
    for (int i = 0; i < route.size(); ++i) {
        std::cout << route[i];
        if (i != route.size() - 1)
            std::cout << " -> ";
    }
    std::cout << " -> 0" << std::endl;

    double totalDistance = calculateTotalDistance(route);

    return totalDistance;
}

/**
 * @brief This function calculates the best path using the nearest neighbor algorithm.
 * This function calculates the total distance of a route using the nearest neighbor algorithm.
 * @note complexity: O(V^2) V is the number of vertices in the graph;
 * @return
 */
void Graph::nearestNeighbor(Graph& graph) {
    graph.bestPath.clear();

    Vertex* startVertex = graph.findVertex(0);

    for (Vertex* vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }

    Vertex* currentVertex = startVertex;
    currentVertex->setVisited(true);

    std::vector<int> currentPath;
    currentPath.push_back(currentVertex->getId());

    while (currentPath.size() < graph.getVertexSet().size()) {
        double minDistance = std::numeric_limits<double>::max();
        Vertex* nearestNeighbor = nullptr;

        for (Edge* edge : currentVertex->getAdj()) {
            Vertex* neighbor = edge->getDest();
            if (!neighbor->isVisited() && edge->getWeight() < minDistance) {
                minDistance = edge->getWeight();
                nearestNeighbor = neighbor;
            }
        }

        currentPath.push_back(nearestNeighbor->getId());

        currentVertex = nearestNeighbor;
        currentVertex->setVisited(true);
    }

    currentPath.push_back(startVertex->getId());

    graph.bestPath = currentPath;
}
/**
 * @brief Perform Tabu Search algorithm to find an improved solution.
 * This function implements the Tabu Search algorithm to find an improved solution for a given graph.
 * It iteratively generates neighboring solutions and evaluates their costs. The algorithm maintains
 * a tabu list to prevent revisiting previously visited solutions. If a better neighbor solution is
 * found and it is not in the tabu list, it becomes the current solution. The algorithm stops when either
 * the maximum number of iterations is reached or no improvement is made for a certain number of iterations.
 * @param graph A reference to the graph on which to perform Tabu Search.
 * @param maxIterations The maximum number of iterations to perform.
 * @param tabuListSize The size of the tabu list.
 * @param maxIterationsWithoutImprovement The maximum number of iterations without improvement to stop the algorithm.
 * @note The complexity of this function depends on the size of the tabu list, the number of iterations.
 */
void Graph::tabuSearch(Graph& graph, int maxIterations, int tabuListSize, int maxIterationsWithoutImprovement) {
    std::deque<std::vector<int>> tabuList;

    std::vector<int> currentSolution = graph.bestPath;
    double currentCost = graph.evaluateSolution(graph, currentSolution);

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Initial path: ";
    for (int i = 0; i < currentSolution.size(); i++) {
        std::cout <<  currentSolution[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Initial cost: " << currentCost << std::endl;

    tabuList.push_front(currentSolution);

    int iterationsWithoutImprovement = 0;

    for (int iteration = 0; iteration < maxIterations; iteration++) {
        std::vector<int> bestNeighbor = generateNeighborSolution(currentSolution);
        double bestNeighborCost = graph.evaluateSolution(graph, bestNeighbor);

        if (bestNeighborCost < currentCost &&
            !isTabu(bestNeighbor, tabuList) &&
            (bestNeighborCost < currentCost)) {
            currentSolution = bestNeighbor;
            currentCost = bestNeighborCost;
            iterationsWithoutImprovement = 0;
            tabuList.push_front(bestNeighbor);
        } else {
            iterationsWithoutImprovement++;
        }

        if (tabuList.size() > tabuListSize) {
            tabuList.pop_back();
        }

        //std::cout << "Iteration: " << iteration << ", Best Cost: " << currentCost << ", Tabu List Size: " << tabuList.size() << std::endl;

        if (iterationsWithoutImprovement >= maxIterationsWithoutImprovement) {
            break;
        }
    }

    graph.bestPath = currentSolution;
    graph.bestCost = currentCost;
}

/**
 * @brief Calculate diversity between two solutions.
 * This function calculates the diversity between two solutions by comparing their elements at each position.
 * The diversity is defined as the number of positions where the elements of the two solutions differ.
 * The size of the solutions should be the same for accurate comparison.
 * @param solution1
 * @param solution2
 * @return The diversity between the two solutions.
 */
double calculateDiversity(const std::vector<int>& solution1, const std::vector<int>& solution2) {
    int diversity = 0;
    int size = solution1.size();

    for (int i = 0; i < size; i++) {
        if (solution1[i] != solution2[i]) {
            diversity++;
        }
    }

    return static_cast<double>(diversity) / size;
}

/**
 * @brief Check if a solution is tabu aspirational.
 * This function checks if a solution is tabu aspirational by comparing it with the solutions in the tabu list.
 * A solution is tabu aspirational if its diversity with any of the solutions in the tabu list is greater than
 * the diversification threshold.
 * @param solution
 * @param tabuList
 * @param diversificationThreshold
 * @return True if the solution is tabu aspirational, false otherwise.
 */
bool Graph::isTabuAspirational(const std::vector<int>& solution, const std::deque<std::vector<int>>& tabuList, const double diversificationThreshold) {
    for (const auto& tabuSolution : tabuList) {
        double diversity = calculateDiversity(solution, tabuSolution);
        if (diversity > diversificationThreshold) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Check if a solution is tabu.
 * This function checks if a solution is tabu by comparing it with the solutions in the tabu list.
 * @param solution
 * @param tabuList
 * @return True if the solution is tabu, false otherwise.
 */
bool Graph::isTabu(const std::vector<int>& solution, const std::deque<std::vector<int>>& tabuList) {
    for (const auto& tabuSolution : tabuList) {
        if (solution == tabuSolution) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Perform the Simulated Annealing algorithm on the graph.
 * This function applies the Simulated Annealing algorithm to find an optimal solution for the given graph.
 * It starts with an initial solution and iteratively explores neighboring solutions by accepting or rejecting them based on a probability.
 * The algorithm aims to converge towards the global optimum by gradually decreasing the acceptance probability with each iteration.
 * @param graph The graph on which to perform the Simulated Annealing algorithm.
 * @param maxIterations The maximum number of iterations to perform.
 * @param initialTemperature The initial temperature for the annealing process.
 * @param coolingRate The cooling rate for the annealing process.
*/
void Graph::simulatedAnnealing(Graph& graph, int maxIterations, double initialTemperature, double coolingRate) {
    std::vector<int> currentSolution = bestPath;
    double currentCost = graph.evaluateSolution(graph, currentSolution);

    std::vector<int> bestSolution = currentSolution;
    double bestCost = currentCost;

    double temperature = initialTemperature;

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Initial path: ";
    for (int i = 0; i < currentSolution.size(); i++) {
        std::cout <<  currentSolution[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Initial cost: " << currentCost << std::endl;

    for (int iteration = 0; iteration < maxIterations; iteration++) {
        std::vector<int> candidateSolution = generateNeighborSolution(currentSolution);
        double candidateCost = evaluateSolution(graph, candidateSolution);

        double acceptanceProb = acceptanceProbability(currentCost, candidateCost, temperature);
        if (acceptanceProb > (std::rand() / (RAND_MAX + 1.0))) {
            currentSolution = candidateSolution;
            currentCost = candidateCost;
        }

        if (candidateCost < bestCost) {
            bestSolution = candidateSolution;
            bestCost = candidateCost;
        }

        temperature *= coolingRate;

        //std::cout << "Iteration: " << iteration << ", Best Cost: " << currentCost << ", Temperature: " << temperature << std::endl;
    }

    graph.bestPath = bestSolution;
    graph.bestCost = bestCost;
}

/**
 * @brief Generate a neighboring solution based on a given solution.
 * This function generates a neighboring solution by applying a random mutation to the given solution.
 * The mutation can be one of four types: swap, deletion, reversal, or scramble.
 * @param solution The current solution for which to generate a neighbor.
 * @return A neighboring solution obtained by applying a random mutation to the given solution.
 * @note The function creates a copy of the given solution and performs a random mutation on the copy.
 * @param solution
 * @return
 */
std::vector<int> Graph::generateNeighborSolution(const std::vector<int>& solution) {
    std::vector<int> neighbor = solution;
    int size = neighbor.size();
    int mutationType = rand() % 4;

    switch (mutationType) {
        case 0: {
            int randomIndex1, randomIndex2;
            do {
                randomIndex1 = 1 + rand() % (size - 2);
                randomIndex2 = 1 + rand() % (size - 2);
            } while (randomIndex1 == randomIndex2);
            std::swap(neighbor[randomIndex1], neighbor[randomIndex2]);
            break;
        }
        case 1: {
            int randomIndex1 = 1 + rand() % (size - 2);
            int element = neighbor[randomIndex1];

            neighbor.erase(neighbor.begin() + randomIndex1);

            int insertIndex = 1 + rand() % (size - 2);

            neighbor.insert(neighbor.begin() + insertIndex, element);
            break;
        }
        case 2: {
            int startIndex = 1 + rand() % (size - 3);
            int endIndex = startIndex + 1 + rand() % (size - startIndex - 2);

            std::reverse(neighbor.begin() + startIndex, neighbor.begin() + endIndex + 1);
            break;
        }
        case 3: {
            int scrambleStart = 1 + rand() % (size - 3);
            int scrambleEnd = scrambleStart + 1 + rand() % (size - scrambleStart - 2);

            std::random_shuffle(neighbor.begin() + scrambleStart, neighbor.begin() + scrambleEnd + 1);
            break;
        }
        default:
            break;
    }

    return neighbor;
}

/**
 * @brief Calculate the acceptance probability for a candidate solution.
 * @param currentCost
 * @param candidateCost
 * @param temperature
 * @return
 */
double Graph::acceptanceProbability(double currentCost, double candidateCost, double temperature) {
    if (candidateCost < currentCost) {
        return 1.0;
    }
    return std::exp((currentCost - candidateCost) / temperature);
}

/**
 * @brief Generate a random solution for the graph.
 * This function generates a random solution for the graph by randomly shuffling the vertices.
 * @return A random solution for the graph.
 */
std::vector<int> Graph::generateRandomSolution() {
    std::vector<int> randomSolution;
    std::vector<Vertex*> vertices = getVertexSet();

    vertices.erase(vertices.begin());

    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(vertices.begin(), vertices.end(), generator);

    randomSolution.push_back(0);
    for (Vertex* vertex : vertices) {
        randomSolution.push_back(vertex->getId());
    }
    randomSolution.push_back(0);

    return randomSolution;
}

/**
 * @brief Evaluate a solution for the graph.
 * This function evaluates a solution for the graph by calculating the total cost of the solution.
 * @param graph
 * @param solution
 * @return
 */
double Graph::evaluateSolution(Graph& graph, const std::vector<int>& solution) {
    double totalCost = 0.0;

    for (size_t i = 0; i < solution.size() - 1; i++) {
        int sourceID = solution[i];
        int destID = solution[i + 1];
        Vertex* source = graph.findVertex(sourceID);

        Edge* edge = nullptr;
        for (Edge* adjEdge : source->getAdj()) {
            if (adjEdge->getDest()->getId() == destID) {
                edge = adjEdge;
                break;
            }
        }

        totalCost += edge->getWeight();
    }

    return totalCost;
}

/**
 * @brief Construct a minimum spanning tree for the graph.
 * This function constructs a minimum spanning tree for the graph.
 * @return A minimum spanning tree for the graph.
 * @param graph
 * @return
 */
Graph Graph::constructMST(Graph& graph) {
    Graph mstGraph;

    std::vector<Vertex*> mstVertices = graph.MST();

    std::unordered_set<Vertex*> visitedVertices;

    for (Vertex* vertex : mstVertices) {
        mstGraph.addVertex(vertex->getId(),0,0);
        visitedVertices.insert(vertex);
    }

    for (Vertex* vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }

    for (const Vertex* vertex : graph.getVertexSet()) {
        if (vertex->getPath() != nullptr) {
            const Edge* edge = vertex->getPath();
            Vertex* origin = edge->getOrig();
            Vertex* dest = edge->getDest();

            if (!origin->isVisited() && !dest->isVisited()) {
                mstGraph.addBidirectionalEdge(origin->getId(), dest->getId(), edge->getWeight());
                visitedVertices.insert(origin);
                visitedVertices.insert(dest);
            }
        }
    }

    return mstGraph;
}

/**
 * @brief Construct a minimum spanning tree for the graph.
 * This function constructs a minimum spanning tree for the graph.
 * @return
 */
std::vector<Vertex *> Graph::MST() {
    if (vertexSet.empty()) {
        return this->vertexSet;
    }

    for(auto v : vertexSet) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    Vertex* s = vertexSet.front();
    s->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(s);
    while( ! q.empty() ) {
        auto v = q.extractMin();
        v->setVisited(true);
        for(auto &e : v->getAdj()) {
            Vertex* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if(e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());
                    w->setPath(e);
                    if (oldDist == INF) {
                        q.insert(w);
                    }
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }

    return this->vertexSet;
}

/**
 * @brief Find the vertices with odd degrees in the graph.
 * This function finds the vertices with odd degrees in the graph.
 * @param graph
 * @return
 */
std::vector<Vertex*> Graph::findVerticesWithOddDegrees(const Graph& graph) {
    for (Vertex* vertex : graph.getVertexSet()) {
        vertex->setIndegree(0);
    }

    std::vector<Vertex*> oddDegreeVertices;
    for (const Vertex* vertex : graph.getVertexSet()) {
        int totalDegree = vertex->getIndegree();
        for (const Edge* edge : vertex->getIncoming()) {
            Vertex* sourceVertex = edge->getOrig();
            totalDegree++;
            totalDegree += sourceVertex->getIndegree();
        }
        if (totalDegree % 2 == 1) {
            oddDegreeVertices.push_back(const_cast<Vertex*>(vertex));
        }
    }

    return oddDegreeVertices;
}

/**
 * @brief Find the minimum weight matching for the graph.
 * This function finds the minimum weight matching for the graph.
 * @param graph
 * @param oddDegreeVertices
 * @return
 */
Graph Graph::findMinimumWeightMatching(const Graph& graph, const std::vector<Vertex*>& oddDegreeVertices) {
    Graph matchingGraph;

    for (Vertex* vertex : oddDegreeVertices) {
        matchingGraph.addVertex(vertex->getId(),0,0);
    }

    std::vector<bool> visited(oddDegreeVertices.size(), false);
    for (std::size_t i = 0; i < oddDegreeVertices.size(); ++i) {
        if (!visited[i]) {
            double minWeight = std::numeric_limits<double>::max();
            Vertex* minVertex = nullptr;
            for (std::size_t j = i + 1; j < oddDegreeVertices.size(); ++j) {
                if (!visited[j]) {
                    double weight = graph.getEdgeWeight(oddDegreeVertices[i]->getId(), oddDegreeVertices[j]->getId());
                    if (weight < minWeight) {
                        minWeight = weight;
                        minVertex = oddDegreeVertices[j];
                    }
                }
            }
            visited[i] = true;
            if (minVertex) {
                visited[std::distance(oddDegreeVertices.begin(), std::find(oddDegreeVertices.begin(), oddDegreeVertices.end(), minVertex))] = true;
                matchingGraph.addEdge(oddDegreeVertices[i]->getId(), minVertex->getId(), minWeight);
            }
        }
    }

    return matchingGraph;
}


/**
 * @brief Combine the minimum spanning tree and the minimum weight matching.
 * This function combines the minimum spanning tree and the minimum weight matching.
 * @param mstGraph
 * @param matchingGraph
 * @return
 */
Graph Graph::combineGraphs(const Graph& mstGraph, const Graph& matchingGraph) {
    Graph multigraph = mstGraph;

    for (const Vertex* vertex : matchingGraph.getVertexSet()) {
        for (const Edge* edge : vertex->getAdj()) {
            multigraph.addBidirectionalEdge(edge->getOrig()->getId(), edge->getDest()->getId(), edge->getWeight());
        }
    }

    return multigraph;
}

/**
 * @brief Find an Eulerian circuit for the multigraph.
 * This function finds an Eulerian circuit for the multigraph.
 * @param multigraph
 * @note complexity: O(|E| + |V|)
 * @return
 */
std::vector<int> Graph::findEulerianCircuit(Graph& multigraph) {
    std::vector<int> circuit;

    const Vertex* startVertex = multigraph.getVertexSet()[0];

    std::stack<Vertex*> vertexStack;
    vertexStack.push(const_cast<Vertex*>(startVertex));

    while (!vertexStack.empty()) {
        Vertex* currentVertex = vertexStack.top();

        if (currentVertex->getAdj().empty()) {
            circuit.push_back(currentVertex->getId());
            vertexStack.pop();
        } else {
            Edge* nextEdge = currentVertex->getAdj().front();
            currentVertex->removeEdge(nextEdge->getDest()->getId());
            vertexStack.push(nextEdge->getDest());
        }
    }

    std::reverse(circuit.begin(), circuit.end());

    return circuit;
}

/**
 * @brief Remove duplicate vertices from the Eulerian circuit.
 * @param eulerianCircuit
 * @return
 */
std::vector<int> Graph::removeDuplicates(const std::vector<int>& eulerianCircuit) {
    std::vector<int> hamiltonianCircuit;
    std::unordered_set<int> visited;

    for (int vertex : eulerianCircuit) {
        if (visited.count(vertex) == 0 || hamiltonianCircuit.empty()) {
            hamiltonianCircuit.push_back(vertex);
            visited.insert(vertex);
        }
    }

    if (!hamiltonianCircuit.empty()) {
        hamiltonianCircuit.push_back(hamiltonianCircuit.front());
    }

    return hamiltonianCircuit;
}

/**
 * @brief This function implements the Christofides algorithm.
 * This function implements the Christofides algorithm.
 * @note complexity: O(V^3)
 * @param graph
 */
void Graph::christofidesAlgorithm(Graph& graph) {
    graph.bestPath.clear();
    graph.bestCost = std::numeric_limits<double>::max();
    Graph mstGraph = constructMST(graph);

    std::vector<Vertex*> oddDegreeVertices = findVerticesWithOddDegrees(mstGraph);

    Graph matchingGraph = findMinimumWeightMatching(graph, oddDegreeVertices);

    Graph multigraph = combineGraphs(mstGraph, matchingGraph);

    std::vector<int> eulerianCircuit = findEulerianCircuit(multigraph);

    std::vector<int> hamiltonianCircuit = removeDuplicates(eulerianCircuit);

    graph.bestPath = hamiltonianCircuit;
    graph.bestCost = evaluateSolution(graph, graph.bestPath);
}

/**
 * @brief Get the edge weight between two vertices.
 * @param source
 * @param destination
 * @return
 */
double Graph::getEdgeWeight(int source, int destination) const {
    Vertex* sourceVertex = findVertex(source);
    if (sourceVertex == nullptr) {
        return std::numeric_limits<double>::max();
    }

    for (Edge* edge : sourceVertex->getAdj()) {
        if (edge->getDest()->getId() == destination) {
            return edge->getWeight();
        }
    }

    return std::numeric_limits<double>::max();
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}
