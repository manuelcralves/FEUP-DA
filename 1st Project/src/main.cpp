#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <unordered_map>
#include "data_structures/Graph.h"


using namespace std;
/**

@brief Parses a line of CSV (Comma-Separated Values) and returns a vector of fields.
This function takes a line of text in CSV format and splits it into fields using commas as delimiters.
Fields enclosed in double quotes are treated as a single field, even if they contain commas.
The resulting fields are stored in a vector of strings.
@param line The input string containing the CSV line to be parsed.
@return A vector of strings representing the fields extracted from the CSV line.
*/
vector<string> parse_csv_line(const std::string& line);

/**

@brief Reads station information from a CSV file and stores it in an unordered map.
This function reads station information from a CSV file, where each line represents a station
with various attributes separated by commas. The information is parsed using the parse_csv_line()
function, and a new Vertex object is created for each station using the parsed fields. The Vertex
objects are added to a Graph object, and the station names are used as keys in an unordered map
to store the corresponding Vertex pointers.
@param railway A reference to the Graph object to which the Vertex objects will be added.
@return An unordered map with station names as keys and Vertex pointers as values.
@throw runtime_error If the stations.csv file cannot be opened.
*/
unordered_map<string, Vertex *> readStations(Graph& railway);

/**

@brief Reads network information from a CSV file and updates a Graph object.
This function reads network information from a CSV file, where each line represents a connection
between two stations with various attributes separated by commas. The information is parsed using
the parse_csv_line() function, and the corresponding Vertex pointers are retrieved from the
provided unordered map of stations. The railway Graph object is then updated with bidirectional
edges between the stations using the addBidirectionalEdge() function, with the parsed attributes
such as weight and edge label.
@param railway A reference to the Graph object to be updated with network information.
@param stations An unordered map with station names as keys and Vertex pointers as values.
@throw runtime_error If the network.csv file cannot be opened.
*/
void readNetwork(Graph& railway,unordered_map<string, Vertex *> stations);

/**

@brief Reads railway information from CSV files and updates a Graph object.
This function reads railway information from two CSV files: stations.csv and network.csv. The
stations.csv file contains station information, which is read using the readStations() function
to populate an unordered map with station names as keys and Vertex pointers as values. The
network.csv file contains network information, which is read using the readNetwork() function to
update the Graph object with bidirectional edges between stations based on the station map
obtained from readStations().
@param railway A reference to the Graph object to be updated with railway information.
@throw runtime_error If the stations.csv or network.csv files cannot be opened.
*/
void read(Graph& railway);

/**

@brief Performs Breadth-First Search (BFS) algorithm to find a path from source to destination in a Graph.
This function implements the Breadth-First Search (BFS) algorithm to find a path from a given source
Vertex to a destination Vertex in a Graph. It uses a queue data structure to explore the Graph in
breadth-first order, starting from the source Vertex. The Graph is assumed to have already been
populated with Vertex and Edge objects, and their visited and path states are updated during the BFS
traversal.
@param source Pointer to the source Vertex from where the BFS traversal starts.
@param destination Pointer to the destination Vertex that is being searched for.
@param railway A reference to the Graph object in which the BFS traversal is performed.
@return true if a path is found from source to destination, false otherwise.
*/
bool bfs(Vertex* source, Vertex* destination, Graph& railway);

/**

@brief Creates a reduced subgraph of the Graph by removing stations and connections.

This function allows the user to interactively create a reduced subgraph of the Graph by

removing stations and connections between stations. It prompts the user for input to remove

stations and connections, and performs the necessary operations on the Graph object 'railway'

to create the reduced subgraph.

@param railway A reference to the Graph object for which the reduced subgraph is to be created.
*/
void createReducedGraph(Graph &railway);

/**

@brief Prints information about an Edge object.
This function generates a string representation of the Edge object, including its origin and destination station names,
capacity, and service information. The generated string is formatted with a delimiter of a certain column size, and
each field is displayed in a separate line.
@param edge Pointer to the Edge object to be printed.
@return void
*/
void printEdgeInfo(const Edge* edge);

/**

@brief Pauses program execution and waits for user input to continue.
This function displays a prompt message to the user to press ENTER to continue, and then waits for the user to press
ENTER before continuing with the program execution. It uses the std::cin.ignore() function to discard any remaining
input in the input stream, allowing the program to wait for user input.
@return void
*/
void pause();

/**

@brief Displays the interface menu for a Railway Management System and handles user input.
This function displays a menu with options for different functionalities of a Railway Management System. It prompts the
user to enter their choice, validates the input, and calls the corresponding function based on the user's choice.
If the user enters an invalid option, they are prompted to enter a valid option until a valid choice is made.
The function uses a switch statement to execute the appropriate functionality based on the user's input.
@param railway A reference to a Graph object representing the railway network.
@return void
*/
void interface(Graph& railway);

/**

@brief Provides basic service metrics for a Railway Management System.
This function displays a menu with options for various basic service metrics of a Railway Management System.
It prompts the user to enter their choice, validates the input, and calls the corresponding function based on the user's choice.
If the user enters an invalid option, they are prompted to enter a valid option until a valid choice is made.
The function uses a switch statement to execute the appropriate functionality based on the user's input.
@param railway A reference to a Graph object representing the railway network.
@return void
*/
void basicServiceMetrics(Graph& railway); // 4.1

/**

@brief Calculates the maximum number of trains that can simultaneously travel between two specific stations in a railway network.
This function prompts the user to enter the names of the source and destination stations.
It then calls the Edmonds-Karp algorithm on the Graph object to find the maximum flow between the source and destination stations,
which represents the maximum number of trains that can simultaneously travel between the two stations.
The calculated result is displayed on the console.
@param railway A reference to a Graph object representing the railway network.
@return void
*/
void maxTrainsBetweenStations(Graph& railway);

/**

@brief Determines which stations in a railway network require the most amount of trains.
This function calls the MaxFlowBetweenPairs() function on the Graph object to calculate the maximum flow
between all pairs of source and destination stations in the railway network.
The maximum flow represents the maximum number of trains that can simultaneously travel between each pair of stations.
The function then determines which stations require the most amount of trains based on the calculated maximum flows,
and displays the results on the console.
@param railway A reference to a Graph object representing the railway network.
@return void
*/
void mostTrainsRequired(Graph& railway);

/**

@brief Assigns larger budgets for the purchasing and maintenance of trains in a railway network.
This function calls the topDistricts() and topMunicipalities() functions on the Graph object to identify
the top districts and municipalities in the railway network that require larger budgets for the purchasing
and maintenance of trains. The top districts and municipalities are determined based on various metrics,
such as passenger demand, train usage, and revenue generated.
The function then displays the results on the console, indicating the districts and municipalities that require
larger budgets for train operations.
@param railway A reference to a Graph object representing the railway network.
@return void
*/
void assignBudgets(Graph& railway);

/**

@brief Reports the maximum number of trains that can simultaneously arrive at a given station in a railway network.
This function takes a Graph object representing the railway network as input and prompts the user to enter the name
of a station for which the maximum number of trains that can simultaneously arrive needs to be calculated.
It then calls the maxTrainsAtStation() function on the Graph object, passing the station as an argument, to calculate
and report the maximum number of trains that can simultaneously arrive at the given station based on the network's
capacity constraints.
@param railway A reference to a Graph object representing the railway network.
@return void
*/
void maxTrainsAtStation(Graph& railway);

/**

@brief Performs operations cost optimization in a railway network.
This function presents a menu of options to the user for operations cost optimization in a railway network.
The user can choose to calculate the maximum amount of trains that can simultaneously travel between two specific stations
with minimum cost. The function then calls the appropriate function based on the user's choice to perform the
operations cost optimization.
@param railway A reference to a Graph object representing the railway network.
@return void
*/
void operationCostOptimization(Graph& railway); //4.2

/**

@brief Calculates the maximum amount of trains that can simultaneously travel between two specific stations with minimum cost.

This function takes a railway network represented by a Graph object and prompts the user to enter the source and destination

station names. It then calculates the maximum amount of trains that can simultaneously travel between the source and destination

stations with minimum cost, using the Ford-Fulkerson algorithm with the BFS-based augmenting path finding method. The function

updates the flow along the augmenting path with the optimal service type, and keeps track of the maximum flow and total cost of

trains allocated along the augmenting path. Finally, it prints the maximum flow and total cost to the console.

@param railway A reference to a Graph object representing the railway network.

@return void
*/
void minCostTrains(Graph& railway);

/**

@brief Generates a report on stations that are the most affected by each segment failure or calculates the maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity.
This function presents a menu with three options:
Calculate the maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity.
Provide a report on the stations that are the most affected by each segment failure.
Return to the previous menu.
@param railway The Graph object representing the railway network.
@return void
*/
void randStoLineFailures(Graph& railway); //4.3

/**

@brief Calculates the maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity.
This function creates a reduced graph from the original railway network using the createReducedGraph() function, and then calculates the maximum number of trains that can simultaneously travel between two specific stations in the reduced graph using the maxTrainsBetweenStations() function.
@param railway The Graph object representing the railway network.
@return void
*/
void maxTrainsReducedConnectivity(Graph& railway);

/**

@brief Provides a report on the stations that are the most affected by each segment failure in a railway network with reduced connectivity.
This function creates a reduced graph from the original railway network using the createReducedGraph() function. Then, it identifies the most affected stations by each segment failure in the reduced graph using the MostAffectStations() function. It displays the list of most affected stations, if any, and pauses for user input before returning.
@param railway The Graph object representing the railway network.
@return void
*/
void mostAffectedStations(Graph& railway);

int main() {
    Graph railway = Graph();
    read(railway);
    interface(railway);
    return 0;
}

vector<string> parse_csv_line(const std::string& line) {
    vector<std::string> fields;
    string field;
    bool in_quotes = false;

    for (size_t i = 0; i < line.length(); ++i) {
        if (line[i] == '"') {
            in_quotes = !in_quotes;
            continue;
        }
        if (line[i] == ',' && !in_quotes) {
            fields.push_back(field);
            field.clear();
        } else {
            field += line[i];
        }
    }
    fields.push_back(field);
    return fields;
}

unordered_map<string, Vertex *> readStations(Graph& railway) {
    ifstream fin("../dataset/stations.csv");
    string line;
    unordered_map<string, Vertex *> stations;
    if (!fin.is_open()) {
        throw runtime_error("Error reading stations.csv");
    }
    getline(fin, line);
    while (getline(fin, line)) {
        if (line[line.size() - 1] == '\r') {
            line.pop_back();
        }
        vector<string> curr = parse_csv_line(line);
        Vertex *vertex = new Vertex(curr[0], curr[1], curr[2], curr[3], curr[4]);
        railway.addVertex(vertex);
        stations.insert(make_pair(curr[0], vertex));
    }
    fin.close();
    return stations;
}

void readNetwork(Graph& railway,unordered_map<string, Vertex *> stations){
    ifstream fin("../dataset/network.csv");
    string line;
    if(!fin.is_open()) {
        throw runtime_error("Error reading network.csv");
    }
    getline(fin, line);
    while (getline(fin, line)) {
        if (line[line.size() - 1] == '\r') {
            line.pop_back();
        }
        vector<string> curr = parse_csv_line(line);
        Vertex* stationA = stations.find(curr[0])->second;
        Vertex* stationB = stations.find(curr[1])->second;
        railway.addBidirectionalEdge(stationA,stationB,stod(curr[2]),curr[3]);
    }
    fin.close();
}

void read(Graph& railway){
    readNetwork(railway, readStations(railway));
}

void interface(Graph& railway){
    int option;
    cout << "\n--- Railway Management System Interface Menu ---\n" << endl;
    cout << "1. - Basic Service Metrics" << endl;
    cout << "2. - Operations Cost Optimization" << endl;
    cout << "3. - Reliability and Sensitivity to Line Failures" << endl;
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
            basicServiceMetrics(railway);
            break;
        case 2:
            operationCostOptimization(railway);
            break;
        case 3:
            randStoLineFailures(railway);
            break;
        case 4:
            exit(-1);
    }
}
void basicServiceMetrics(Graph& railway){
    int option;
    cout << "\n--- Basic Service Metrics ---\n" << endl;
    cout << "1. - Calculate the maximum number of trains that can simultaneously travel between two specific stations" << endl;
    cout << "2. - Determine which stations require the most amount of trains" << endl;
    cout << "3. - Assign larger budgets for the purchasing and maintenance of trains" << endl;
    cout << "4. - Report the maximum number of trains that can simultaneously arrive at a given station" << endl;
    cout << "5. - Return\n" << endl;
    cout << "Enter your option: ";
    cin >> option;
    while (option < 1 || option > 5) {
        cout << "This option is not valid, try again!" << endl;
        cout << "Option:";
        cin >> option;
    }
    switch (option) {
        case 1:
            std::cin.ignore();
            maxTrainsBetweenStations(railway);
            break;
        case 2:
            mostTrainsRequired(railway);
            break;
        case 3:
            assignBudgets(railway);
            break;
        case 4:
            maxTrainsAtStation(railway);
            break;
        case 5:
            interface(railway);
            break;
    }
}

void operationCostOptimization(Graph& railway) {
    int option;
    cout << "\n--- Operations Cost Optimization ---\n" << endl;
    cout << "1. - Calculate the maximum amount of trains that can simultaneously travel between two specific stations with minimum cost" << endl;
    cout << "2. - Return\n" << endl;
    cout << "Enter your option: ";
    cin >> option;
    while (option < 1 || option > 2) {
        cout << "This option is not valid, try again!" << endl;
        cout << "Option:";
        cin >> option;
    }
    switch (option) {
        case 1:
            minCostTrains(railway);
            break;
        case 2:
            interface(railway);
            break;
    }
}

void randStoLineFailures(Graph& railway){
    int option;
    cout << "1. - Calculate the maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity" << endl;
    cout << "2. - Provide a report on the stations that are the most affected by each segment failure" << endl;
    cout << "3. - Return\n" << endl;
    cout << "Enter your option: ";
    cin >> option;
    while (option < 1 || option > 3) {
        cout << "This option is not valid, try again!" << endl;
        cout << "Option:";
        cin >> option;
    }
    switch (option) {
        case 1:
            maxTrainsReducedConnectivity(railway);
            break;
        case 2:
            mostAffectedStations(railway);
            break;
        case 3:
            interface(railway);
            break;

    }
}
void maxTrainsBetweenStations(Graph& railway){
    std::string sourceName;
    int option;
    std::cout << "Enter source station name: ";
    std::getline(std::cin, sourceName);
    Vertex* source = railway.findVertex(sourceName);
    if (source == nullptr) {
        std::cout << "Source station not found." << std::endl;
        return;
    }

    // Get destination station
    std::string destName;
    std::cout << "Enter destination station name: ";
    std::getline(std::cin, destName);
    Vertex* destination = railway.findVertex(destName);
    if (destination == nullptr) {
        std::cout << "Destination station not found." << std::endl;
        return;
    }
    double maxTrains = railway.EdmondsKarp(source, destination);
    std::cout << "Max trains between " << sourceName << " and " << destName << " is " << maxTrains << endl;
}

void mostTrainsRequired(Graph& railway){
    railway.MaxFlowBetweenPairs();
}

void assignBudgets(Graph& railway){
    int option;
    int k;
    cout << "1 - Top Districts" << endl;
    cout << "2 - Top Municipalities" << endl;
    cin >> option;
    cout << "Choose the number of options :" << endl;
    cin >> k;
    switch (option) {
        case 1:
            railway.topDistricts(k);
            break;
        case 2:
            railway.topMunicipalities(k);
            break;

    }
}

void maxTrainsAtStation(Graph& railway){
    std::string stationName;
    std::cout << "Enter station name: ";
    std::cin.ignore();
    std::getline(std::cin, stationName);
    Vertex* station = railway.findVertex(stationName);
    if (station == nullptr) {
        std::cout << "Source station not found." << std::endl;
        return;
    }
    railway.maxTrainsAtStation(station);
}

void minCostTrains(Graph& railway) {
    // Get source station
    std::string sourceName;
    std::cout << "Enter source station name: ";
    std::cin.ignore();
    std::getline(std::cin, sourceName);
    Vertex* source = railway.findVertex(sourceName);
    if (source == nullptr) {
        std::cout << "Source station not found." << std::endl;
        return;
    }

    // Get destination station
    std::string destName;
    std::cout << "Enter destination station name: ";
    std::getline(std::cin, destName);
    Vertex* destination = railway.findVertex(destName);
    if (destination == nullptr) {
        std::cout << "Destination station not found." << std::endl;
        return;
    }

    int maxFlow = 0;
    double totalCost = 0.0; // Total cost of trains allocated along augmenting path

    // Initialize residual graph with the same capacities as original graph
    for (Vertex* v : railway.getVertexSet()) {
        for (Edge* e : v->getAdj()) {
            e->setFlow(0);
        }
    }

    // Loop until there is an augmenting path from source to destination
    while (bfs(source, destination, railway)) {
        // Find the bottleneck capacity along the augmenting path
        double bottleneck = INF;
        Vertex* v = destination;
        std::string optimalServiceType = ""; // Stores the optimal service type for the bottleneck capacity
        while (v != source) {
            Edge* e = v->getPath();
            double remainingCapacity = e->getWeight() - e->getFlow();
            std::string service = e->getService();
            double cost = 0.0;
            if (service == "STANDARD") {
                cost = 2.0; // Standard service cost is 2€ per train
            } else if (service == "ALFA PENDULAR") {
                cost = 4.0; // Alpha service cost is 4€ per train
            } else {
                std::cout << "Invalid service type encountered: " << service << std::endl;
                return;
            }
            // Calculate the cost of trains for the remaining capacity of the edge
            double trainCost = cost * remainingCapacity;
            // Update the optimal service type if the current service type has lower cost per train
            if (optimalServiceType.empty() || trainCost < (cost * bottleneck)) {
                bottleneck = remainingCapacity;
                optimalServiceType = service;
            }
            v = e->getOrig();
        }

        // Update the flow along the augmenting path with the optimal service type
        v = destination;
        while (v != source) {
            Edge* e = v->getPath();
            e->setFlow(e->getFlow() + bottleneck);
            e->getReverse()->setFlow(e->getReverse()->getFlow() - bottleneck);
            v = e->getOrig();
        }

        maxFlow += bottleneck;
        // Update the total cost with the cost of trains allocated using the optimal service type
        if (optimalServiceType == "STANDARD") {
            totalCost += 2.0 * bottleneck;
        } else if (optimalServiceType == "ALFA PENDULAR") {
            totalCost += 4.0 * bottleneck;
        }
    }

    std::cout << "Max Flow between " << sourceName << " and " << destName << " is " << maxFlow << ", with Min Cost " << totalCost << "€" << endl;
}

// Function to perform breadth-first search (BFS) to find an augmenting path
bool bfs(Vertex* source, Vertex* destination, Graph& railway) {
    for (Vertex* v : railway.getVertexSet()) {
        v->setVisited(false);
        v->setPath(nullptr);
    }

    std::queue<Vertex*> queue;
    queue.push(source);
    source->setVisited(true);

    while (!queue.empty()) {
        Vertex* v = queue.front();
        queue.pop();

        for (Edge* e : v->getAdj()) {
            Vertex* u = e->getDest();
            if (!u->isVisited() && e->getWeight() > e->getFlow()) {
                u->setVisited(true);
                u->setPath(e);
                queue.push(u);
            }
        }
    }

    return destination->isVisited();
}

void createReducedGraph(Graph& railway) {
    cout << "Create the reduced subgraph" << endl << endl;
    char opt = 'n';

    cout << "Do you want to remove a station? (y/n): ";
    cin >> opt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool removeStations = (opt == 'y' || opt == 'Y');

    while (removeStations) {
        cout << "Insert the name of the station you want to remove: ";
        string stationName;
        getline(cin, stationName);

        if (!railway.removeVertex(stationName)) {
            cout << "Invalid station!\n";
        }

        opt = 'n';
        cout << "Want to remove another station? (y/n): ";
        cin >> opt;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opt == 'n' || opt == 'N') {
            break;
        }

    }

    opt = 'n';
    cout << "Do you want to remove a connection between 2 stations? (y/n): ";
    cin >> opt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool removeEdges = (opt == 'y' || opt == 'Y');

    while (removeEdges) {
        cout << "Insert the name of the origin station: ";
        string originName;
        getline(cin, originName);

        auto origin = railway.findVertex(originName);
        if (origin == nullptr) {
            cout << "Invalid station!\n";

            opt = 'n';
            cout << "Want to remove another connection? (y/n): ";
            cin >> opt;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (opt == 'n' || opt == 'N') {
                break;
            }

            continue;
        }

        cout << "Insert the name of the destination station: ";
        string destName;
        getline(cin, destName);

        auto dest = railway.findVertex(destName);
        if (dest == nullptr) {
            cout << "Invalid station!\n";

            opt = 'n';
            cout << "Want to remove another connection? (y/n): ";
            cin >> opt;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (opt == 'n' || opt == 'N') {
                break;
            }

            continue;
        }

        bool found = false;
        for (auto e : origin->getAdj()) {
            if (e->getDest()->getName() == destName) {
                printEdgeInfo(e);

                cout << "\nConfirm? (y/n): ";

                opt = 'n';
                cin >> opt;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (opt == 'y' || opt == 'Y') {
                    found = origin->removeEdge(dest->getName());
                }
            }
        }

        if (!found) {
            cout << "Invalid connection!\n\n";
        }

        opt = 'n';
        cout << "Want to remove another connection? (y/n): ";
        cin >> opt;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opt == 'n' || opt == 'N') {
            break;
        }

    }
}


void printEdgeInfo(const Edge* edge) {
    int col_size = 50;

    std::stringstream ss;
    ss << edge->getOrig()->getName() << " -> " << edge->getDest()->getName();
    std::string title = ss.str();

    ss.str("");
    ss << "Capacity: " << edge->getWeight();
    std::string capacity = "| " + ss.str();
    ss.str("");
    ss << "Service: " << edge->getService();
    std::string service = "| " + ss.str();
    ss.str("");

    std::string delimiter(col_size, '-');

    std::cout << delimiter << '\n';
    std::cout << "|" << title << " |\n";
    std::cout << capacity << " |\n";
    std::cout << service << " |\n";
    std::cout << delimiter << '\n';
}


void pause() {
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void maxTrainsReducedConnectivity(Graph& railway){
    createReducedGraph(railway);
    cout << "Max Trains Between Stations in the subgraph" << endl << endl;
    maxTrainsBetweenStations(railway);
}

void mostAffectedStations(Graph& railway){
    Graph rc = railway;
    createReducedGraph(rc);
    std::vector<std::string>v = railway.MostAffectStations(rc);
    if(v.empty()){
        std::cout << "There are no segment failures \n";
        pause();
        return;
    }
    std::cout << "The most affected stations by the segment failure are: \n";
    for(auto i : v){
        std::cout << i << "\n";
    }
    pause();
}
