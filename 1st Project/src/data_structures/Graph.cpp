#include <unordered_set>
#include "Graph.h"

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

bool Graph::removeVertex(const std::string& station_name) {
    Vertex* v = findVertex(station_name);
    if (v == nullptr) {
        return false;
    }

    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        w->removeEdge(v->getName());
        v->removeEdge(w->getName());
    }

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getName() == station_name){
            vertexSet.erase(it);
            break;
        }
    }

    delete v;
    return true;
}

Vertex * Graph::findVertex(const std::string &name) const {
    for (auto v : vertexSet)
        if (v->getName() == name)
            return v;
    return nullptr;
}

bool Graph::addVertex(Vertex* vertex) {
    vertexSet.push_back(vertex);
}

bool Graph::addBidirectionalEdge(Vertex* v1,Vertex* v2, double w,std::string service) {
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w,service);
    auto e2 = v2->addEdge(v1, w,service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void Graph::MaxFlowBetweenPairs() {
    auto start = std::chrono::high_resolution_clock::now();
    double maxflow = -1;
    std::vector<std::pair<Vertex *, Vertex *>> result;

    for (int i = 0; i < vertexSet.size(); i++) {
        for (int j = i + 1; j < vertexSet.size(); j++) {
            Vertex *s = vertexSet[i];
            Vertex *t = vertexSet[j];
            double m = EdmondsKarp(s, t);

            if (m > maxflow) {
                maxflow = m;
                result.clear();
                result.emplace_back(s, t);
            } else if (m == maxflow) {
                result.emplace_back(s, t);
            }
        }
    }

    for (const auto &pair : result) {
        std::cout << pair.first->getName() << " / " << pair.second->getName() << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now(); // Fim do temporizador
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Tempo de execução: " << duration << "ms" << std::endl;
}

void Graph::topDistricts(int k){
    std::map<std::string, double> districtMaxFlows;

    for (int i = 0; i < vertexSet.size(); i++) {
        for (int j = i + 1; j < vertexSet.size(); j++) {
            Vertex *s = vertexSet[i];
            Vertex *t = vertexSet[j];
            if(s->getDistrict() != t->getDistrict()){ // Verificar se os distritos são diferentes
                double maxFlow = EdmondsKarp(s, t);
                districtMaxFlows[s->getDistrict()] += maxFlow;
                districtMaxFlows[t->getDistrict()] += maxFlow;
            }
        }
    }

    std::vector<std::pair<std::string, double>> sortedDistricts(districtMaxFlows.begin(), districtMaxFlows.end());
    std::sort(sortedDistricts.begin(), sortedDistricts.end(), [](const std::pair<std::string, double>& left, const std::pair<std::string, double>& right) {
        return left.second > right.second;
    });

    // Print top districts
    std::cout << "Top districts: \n";
    for (int i = 0; i < k && i < sortedDistricts.size(); i++) { // Verificar o índice para evitar acessar um índice fora do limite
        std::cout << "District: " << sortedDistricts[i].first << ", Max Flow: " << sortedDistricts[i].second << std::endl;
    }
}


void Graph::topMunicipalities(int k) {
    std::map<std::string, double> municipalitiesMaxFlows;

    for (int i = 0; i < vertexSet.size(); i++) {
        for (int j = i + 1; j < vertexSet.size(); j++) {
            Vertex *s = vertexSet[i];
            Vertex *t = vertexSet[j];
            if(s->getMunicipality() != t->getMunicipality()){ // Verificar se os municípios são diferentes
                double maxFlow = EdmondsKarp(s, t);
                municipalitiesMaxFlows[s->getMunicipality()] += maxFlow;
                municipalitiesMaxFlows[t->getMunicipality()] += maxFlow;
            }
        }
    }

    std::vector<std::pair<std::string, double>> sortedMunicipalities(municipalitiesMaxFlows.begin(), municipalitiesMaxFlows.end());
    std::sort(sortedMunicipalities.begin(), sortedMunicipalities.end(), [](const std::pair<std::string, double>& left, const std::pair<std::string, double>& right) {
        return left.second > right.second;
    });

    std::cout << "Top municipalities: \n";
    for (int i = 0; i < k && i < sortedMunicipalities.size(); i++) { // Verificar o índice para evitar acessar um índice fora do limite
        std::cout << "Municipalities: " << sortedMunicipalities[i].first << ", Max Flow: " << sortedMunicipalities[i].second << std::endl;
    }
}

void Graph::maxTrainsAtStation(Vertex *station) {
    // Adiciona um nó source ao grafo
    Vertex *source = new Vertex("Source");
    addVertex(source);

    // Conecta o nó source a todos os vértices adjacentes à estação
    for (Edge *edge : station->getAdj()) {
        Vertex *adjacentVertex = edge->getDest();
            addBidirectionalEdge(source, adjacentVertex, edge->getWeight(),"-");
        }

    // Executa o algoritmo de fluxo máximo para obter o número máximo
    double maxFlow = EdmondsKarp(source, station);
    std::cout << "Maximum number of trains that can simultaneously arrive at station " << station->getName() << ": " << maxFlow << std::endl;

    // Remove o nó source e as arestas adicionadas ao grafo
    removeVertex(source->getName());
}

double Graph::EdmondsKarp(Vertex* s, Vertex* t) {
    double maxFlow = 0.0;
    auto bfs = [this, &s, &t]() -> double {
        for (auto v: vertexSet) {
            v->setVisited(false);
        }
        std::queue<Vertex *> q;
        s->setVisited(true);
        q.push(s);

        std::unordered_map<Vertex *, Edge *> prev;
        while (!q.empty()) {
            Vertex *currVertex = q.front();
            q.pop();
            if (currVertex == t) break;
            for (auto adj: currVertex->getAdj()) {
                if (adj->getDest()->isVisited() || adj->getWeight() - adj->getFlow() <= 0.0) {
                    continue;
                }
                adj->getDest()->setVisited(true);
                prev[adj->getDest()] = adj;
                q.push(adj->getDest());
            }
        }
        if (prev.find(t) == prev.end()) return 0.0;
        double bottleNeck = std::numeric_limits<double>::max();
        for (auto e = prev[t]; e != nullptr; e = prev[e->getOrig()]) {
            bottleNeck = std::min(bottleNeck, e->getWeight() - e->getFlow());
        }
        for (auto e = prev[t]; e != nullptr; e = prev[e->getOrig()]) {
            e->setFlow(e->getFlow() + bottleNeck);
            e->getReverse()->setFlow(e->getReverse()->getFlow() - bottleNeck);
        }
        return bottleNeck;
    };
    double flow;
    while ((flow = bfs()) > 0.0) {
        maxFlow += flow;
    }
    return maxFlow;
}

std::vector<std::string> Graph::MostAffectStations(Graph rc){
    int maxdiff = -1;
    std::unordered_set<std::string> addedPairs;
    for (auto& source : vertexSet) {
        for (auto& connection : source->getAdj()) {
            Vertex* destinationVertex = connection->getDest();
            const auto& destination = destinationVertex->getName();

            int floworiginal = EdmondsKarp(source, destinationVertex);
            int flowrc = rc.EdmondsKarp(source, destinationVertex);
            if(flowrc != floworiginal){
                if(abs(floworiginal-flowrc) > maxdiff){
                    maxdiff = abs(floworiginal-flowrc);
                    addedPairs.clear();
                    addedPairs.insert(source->getName());
                    addedPairs.insert(destination);
                }
                else if(abs(floworiginal-flowrc) == maxdiff){
                    if(addedPairs.find(destination) == addedPairs.end()){
                        addedPairs.insert(destination);
                    }
                    if(addedPairs.find(source->getName()) == addedPairs.end()){
                        addedPairs.insert(source->getName());
                    }
                }
            }
        }
    }
    std::vector<std::string> result;
    for(auto i: addedPairs){
        result.push_back(i);
    }
    return result;
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
