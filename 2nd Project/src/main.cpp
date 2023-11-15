#include <fstream>
#include <sstream>
#include "Graph.h"
#include <iostream>
#include <chrono>
#include <iomanip>


void interface();

void toy_graphs_menu();

void real_world_menu();

void extra_fully_connected_menu();

void BacktrackAlgorithm(Graph& g);
void triangularApproximation(Graph& g);
void NearestNeighbor(Graph& g);
void TabuSearch(Graph& g);
void SimulatedAnnealing(Graph& g);
void Christofides(Graph& g);
Graph readGraph(std::string dataset);


using namespace std;

int main() {
    Graph establishments = Graph();
    interface();
    return 0;
}

/**
 * @brief Interface menu
 */
void interface(){
    int option;
    cout << "\n--- Travelling Salesperson Problem Interface Menu ---\n" << endl;
    cout << "1. - Toy Graphs" << endl;
    cout << "2. - Real World Graphs" << endl;
    cout << "3. - Extra Fully Connected Graphs" << endl;
    cout << "4. - Exit\n" << endl;
    cout << "Enter your option: ";
    cin >> option;

    while (option < 1 || option > 4) {
        cout << "This option is not valid, try again!" << endl;
        cout << "Option:";
        cin >> option;
    }

    switch (option) {
        case 1:
            toy_graphs_menu();
            break;
        case 2:
            real_world_menu();
            break;
        case 3:
            extra_fully_connected_menu();
            break;
        case 4:
            exit(-1);
            break;
        default:
            break;
    }
}

/**
 * @brief Menu for the toy graphs
 */
void toy_graphs_menu() {
    int option_menu;
    cout << "\n--- Toy Graphs ---\n" << endl;
    cout << "1. - Shipping" << endl;
    cout << "2. - Stadiums" << endl;
    cout << "3. - Tourism" << endl;
    cout << "4. - Return\n" << endl;
    cout << "Enter your option: ";
    cin >> option_menu;

    while (option_menu < 1 || option_menu > 4) {
        cout << "This option is not valid, try again!" << endl;
        cout << "Option:";
        cin >> option_menu;
    }

    Graph g;

    switch (option_menu) {
        case 1:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Toy-Graphs/shipping.csv");
            break;
        case 2:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Toy-Graphs/stadiums.csv");
            break;
        case 3:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Toy-Graphs/tourism.csv");
            break;
        case 4:
            interface();
            break;
        default:
            break;
    }
    BacktrackAlgorithm(g);
    std::cout << "Triangular Approximation: "  << std::endl;
    triangularApproximation(g);
}


/**
 * @brief Reads a graph from a file.
 * @param dataset The path to the file.
 * @return The graph read.
 */
void real_world_menu() {
    int option_menu;
    cout << "\n--- Real World Graphs ---\n" << endl;
    cout << "1. - Graph 1" << endl;
    cout << "2. - Graph 2" << endl;
    cout << "3. - Graph 3" << endl;
    cout << "4. - Return\n" << endl;
    cout << "Enter your option: ";
    cin >> option_menu;

    while (option_menu < 1 || option_menu > 4) {
        cout << "This option is not valid, try again!" << endl;
        cout << "Option:";
        cin >> option_menu;
    }
    Graph g;
    switch (option_menu) {
        case 1:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Real-world Graphs/graph1");
            break;
        case 2:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Real-world Graphs/graph2");
            break;
        case 3:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Real-world Graphs/graph3");
            break;
        case 4:
            interface();
            break;
        default:
            break;
    }
    std::cout << "Triangular Approximation: "  << std::endl;
    triangularApproximation(g);
}

/**
 * @brief Menu for the extra fully connected graphs
 * @details This menu allows the user to choose the number of edges of the graph
 */
void extra_fully_connected_menu() {
    int option_menu;
    cout << "\n--- Extra Fully Connected Graphs ---\n" << endl;
    cout << "1. - 25 Edges" << endl;
    cout << "2. - 50 Edges" << endl;
    cout << "3. - 75 Edges" << endl;
    cout << "4. - 100 Edges" << endl;
    cout << "5. - 200 Edges" << endl;
    cout << "6. - 300 Edges" << endl;
    cout << "7. - 400 Edges" << endl;
    cout << "8. - 500 Edges" << endl;
    cout << "9. - 600 Edges" << endl;
    cout << "10. - 700 Edges" << endl;
    cout << "11. - 800 Edges" << endl;
    cout << "12. - 900 Edges" << endl;
    cout << "13. - Return\n" << endl;
    cout << "Enter your option: ";
    cin >> option_menu;

    while (option_menu < 1 || option_menu > 13) {
        cout << "This option is not valid, try again!" << endl;
        cout << "Option:";
        cin >> option_menu;
    }

    Graph g;

    switch (option_menu) {
        case 1:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Extra_Fully_Connected_Graphs/edges_25.csv");
            break;
        case 2:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Extra_Fully_Connected_Graphs/edges_50.csv");
            break;
        case 3:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Extra_Fully_Connected_Graphs/edges_75.csv");
            break;
        case 4:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Extra_Fully_Connected_Graphs/edges_100.csv");
            break;
        case 5:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Extra_Fully_Connected_Graphs/edges_200.csv");
            break;
        case 6:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Extra_Fully_Connected_Graphs/edges_300.csv");
            break;
        case 7:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Extra_Fully_Connected_Graphs/edges_400.csv");
            break;
        case 8:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Extra_Fully_Connected_Graphs/edges_500.csv");
            break;
        case 9:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Extra_Fully_Connected_Graphs/edges_600.csv");
            break;
        case 10:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Extra_Fully_Connected_Graphs/edges_700.csv");
            break;
        case 11:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Extra_Fully_Connected_Graphs/edges_800.csv");
            break;
        case 12:
            std::cout << "Reading Graph :"  << std::endl;
            g = readGraph("../Extra_Fully_Connected_Graphs/edges_900.csv");
            break;
        case 13:
            interface();
            break;
        default:
            break;
    }
    std::cout << "-------Simulated Annealing-------" << std::endl;
    SimulatedAnnealing(g);
    std::cout << "-------Tabu Search-------" << std::endl;
    TabuSearch(g);
    std::cout << "Triangular Approximation: "  << std::endl;
    triangularApproximation(g);
}

/**
 * @brief Reads a graph from a dataset file and returns the constructed graph.
 * @param dataset The path to the dataset file.
 * @return The constructed graph.
*/
Graph readGraph(std::string dataset) {
    std::string d = dataset;
    Graph g;
    std::ifstream fin(dataset);
    std::string line;
    std::getline(fin, line);
    if (line[line.size() - 1] == '\r') {
        line.pop_back();
    }
    if (line == "origem,destino,distancia") {
        while (std::getline(fin, line)) {
            if (line[line.size() - 1] == '\r') {
                line.pop_back();
            }
            std::stringstream ss(line);
            std::string source, dest;
            double dist;
            int sourceInt, destInt;

            std::getline(ss, source, ',');
            std::getline(ss, dest, ',');
            ss >> dist;
            sourceInt = std::stoi(source);
            destInt = std::stoi(dest);

            if (g.findVertex(sourceInt) == nullptr) {
                g.addVertex(sourceInt,0,0);
            }
            if (g.findVertex(destInt) == nullptr) {
                g.addVertex(destInt,0,0);
            }
            g.addBidirectionalEdge(sourceInt, destInt, dist);
        }
    } else if (line == "origem,destino,distancia,label origem,label destino") {
        while (std::getline(fin, line)) {
            if (line[line.size() - 1] == '\r') {
                line.pop_back();
            }
            std::stringstream ss(line);
            std::string source, dest,dist, sourceLabel, destLabel;
            int sourceInt, destInt;
            double distDouble;

            std::getline(ss, source, ',');
            std::getline(ss, dest, ',');
            std::getline(ss, dist, ',');
            std::getline(ss, sourceLabel, ',');
            ss >> destLabel;
            sourceInt = std::stoi(source);
            destInt = std::stoi(dest);
            distDouble = std::stod(dist);

            if (g.findVertex(sourceInt) == nullptr) {
                g.addVertex(sourceInt,0,0);
                g.findVertex(sourceInt)->setLabel(sourceLabel);
            }
            if (g.findVertex(destInt) == nullptr) {
                g.addVertex(destInt,0,0);
                g.findVertex(destInt)->setLabel(destLabel);
            }
            g.addBidirectionalEdge(sourceInt, destInt, distDouble);
        }
    } else if (dataset == "../Real-world Graphs/graph1" || dataset == "../Real-world Graphs/graph2" || dataset == "../Real-world Graphs/graph3"){
        fin.close();
        dataset += "/nodes.csv";
        std::ifstream fin(dataset);
        std::getline(fin, line);
        if (line[line.size() - 1] == '\r') {
            line.pop_back();
        }
        while (std::getline(fin, line)) {
            if (line[line.size() - 1] == '\r') {
                line.pop_back();
            }
            std::stringstream ss(line);
            std::string id, lon;
            int sourceInt;
            double  sourceLongi, lat;

            std::getline(ss, id, ',');
            std::getline(ss, lon, ',');
            ss >> lat;

            sourceInt = std::stoi(id);
            sourceLongi = std::stod(lon);

            if (g.findVertex(sourceInt) == nullptr) {
                g.addVertex(sourceInt,sourceLongi,lat);
            }

        }
        fin.close();
        d +="/edges.csv";
        std::ifstream f(d);
        std::getline(f, line);
        if (line[line.size() - 1] == '\r') {
            line.pop_back();
        }
        while (std::getline(f, line)) {
            if (line[line.size() - 1] == '\r') {
                line.pop_back();
            }
            std::stringstream ss(line);
            std::string source, dest;
            double dist;
            int sourceInt, destInt;

            std::getline(ss, source, ',');
            std::getline(ss, dest, ',');
            ss >> dist;
            sourceInt = std::stoi(source);
            destInt = std::stoi(dest);

            g.addBidirectionalEdge(sourceInt, destInt, dist);
        }
        f.close();
    } else {
        if (line[line.size() - 1] == '\r') {
            line.pop_back();
        }
        std::stringstream ss(line);
        std::string source, dest;
        double dist;
        int sourceInt, destInt;

        std::getline(ss, source, ',');
        std::getline(ss, dest, ',');
        ss >> dist;
        sourceInt = std::stoi(source);
        destInt = std::stoi(dest);

        if (g.findVertex(sourceInt) == nullptr) {
            g.addVertex(sourceInt,0,0);
        }
        if (g.findVertex(destInt) == nullptr) {
            g.addVertex(destInt,0,0);
        }
        g.addBidirectionalEdge(sourceInt, destInt, dist);
        while(std::getline(fin, line)) {
            if (line[line.size() - 1] == '\r') {
                line.pop_back();
            }
            ss = std::stringstream(line);
            std::getline(ss, source, ',');
            std::getline(ss, dest, ',');
            ss >> dist;
            sourceInt = std::stoi(source);
            destInt = std::stoi(dest);
            if (g.findVertex(sourceInt) == nullptr) {
                g.addVertex(sourceInt,0,0);
            }
            if (g.findVertex(destInt) == nullptr) {
                g.addVertex(destInt,0,0);
            }
            g.addBidirectionalEdge(sourceInt, destInt, dist);
        }
    }
    return g;
}


/**
 * @brief Executes the BacktrackAlgorithm on a given graph.
 * This function performs the BacktrackAlgorithm on the given graph, starting from
 * the initial vertex. It measures the execution time and outputs the best path,
 * best cost, graph size, and execution time.
 * @param g The graph on which to perform the BacktrackAlgorithm.
*/
void BacktrackAlgorithm(Graph& g) {
    int initialVertex = 0;
    std::vector<int> initialPath;
    double initialCost = 0.0;

    auto startTime = std::chrono::steady_clock::now();
    g.backtrack(initialVertex, initialPath, initialCost);
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::vector<int> bestPath = g.getBestPath();
    double bestCost = g.getBestCost();

    std::cout << "Best path: ";
    for (int i = 0; i < bestPath.size(); i++) {
        std::cout << bestPath[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Best cost: " << bestCost << std::endl;
    std::cout << "Graph size:" << g.getVertexSet().size() << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

/**
 * @brief Executes the TabuSearch algorithm on a given graph.
 * Executes the NearestNeighborAlgorithm on a given graph
 * This function performs the NearestNeighborAlgorithm on the given graph.
 * It measures the execution time and outputs the minimum distance found
 * by the algorithm.
 * @param g A pointer to the graph on which to perform the NearestNeighborAlgorithm
*/
void triangularApproximation(Graph& g) {
    clock_t start = clock();

    double ans = g.triangularApproximation();

    clock_t end = clock();

    std::cout << "Minimum Distance: " << ans << std::endl;
    std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

/**
 * @brief Executes the NearestNeighborAlgorithm on a given graph.
 * This function performs the NearestNeighborAlgorithm on the given graph.
 * It measures the execution time and outputs the minimum distance found
 * by the algorithm.
 * @param g A pointer to the graph on which to perform the NearestNeighborAlgorithm
 */

void TabuSearch(Graph& g) {
    std::vector<int> initialPath;

    auto startTime = std::chrono::steady_clock::now();
    g.nearestNeighbor(g);
    g.tabuSearch(g, 100000, 3, 5000);
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::vector<int> bestPath = g.getBestPath();
    double bestCost = g.getBestCost();

    std::cout << "Best path: ";
    for (int i = 0; i < bestPath.size(); i++) {
        std::cout << bestPath[i] << " ";
    }

    std::cout << std::fixed << std::setprecision(2);

    std::cout << std::endl;
    std::cout << "Best cost: " << bestCost << std::endl;
    std::cout << "Graph size:" << g.getVertexSet().size() << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}
/**
 * @brief Executes the SimulatedAnnealing algorithm on a given graph.
 * This function performs the SimulatedAnnealing algorithm on the given graph.
 * It measures the execution time and outputs the best path found
 * by the algorithm, along with its corresponding cost and the graph size.
 * @param g
 */
void SimulatedAnnealing(Graph& g) {
    std::vector<int> initialPath;

    auto startTime = std::chrono::steady_clock::now();
    g.nearestNeighbor(g);
    g.simulatedAnnealing(g, 10000, 1000, 0.99);
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::vector<int> bestPath = g.getBestPath();
    double bestCost = g.getBestCost();

    std::cout << "Best path: ";
    for (int i = 0; i < bestPath.size(); i++) {
        std::cout << bestPath[i] << " ";
    }

    std::cout << std::fixed << std::setprecision(2);

    std::cout << std::endl;
    std::cout << "Best cost: " << bestCost << std::endl;
    std::cout << "Graph size:" << g.getVertexSet().size() << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}
/**
 * @brief Executes the Christofides algorithm on a given graph.
 * This function performs the Christofides algorithm on the given graph.
 * It measures the execution time and outputs the best path found
 * by the algorithm, along with its corresponding cost and the graph size.
 * @param g
 */
void Christofides(Graph& g) {
    std::vector<int> initialPath;

    auto startTime = std::chrono::steady_clock::now();
    g.christofidesAlgorithm(g);
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::vector<int> bestPath = g.getBestPath();
    double bestCost = g.getBestCost();

    std::cout << "Best path: ";
    for (int i = 0; i < bestPath.size(); i++) {
        std::cout << bestPath[i] << " ";
    }

    std::cout << std::fixed << std::setprecision(2);

    std::cout << std::endl;
    std::cout << "Best cost: " << bestCost << std::endl;
    std::cout << "Graph size:" << g.getVertexSet().size() << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}
