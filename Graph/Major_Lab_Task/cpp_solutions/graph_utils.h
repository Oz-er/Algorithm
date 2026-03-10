#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <limits>
#include <queue>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>

const double EARTH_RADIUS_KM = 6371.0;
const double INF = std::numeric_limits<double>::infinity();
const double WALKING_SPEED_KMH = 2.0;

// Convert degrees to radians
inline double deg2rad(double deg) {
    return deg * (M_PI / 180.0);
}

// Calculate Haversine distance between two GPS coordinates
inline double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);
    
    double a = std::sin(dLat/2) * std::sin(dLat/2) +
               std::cos(deg2rad(lat1)) * std::cos(deg2rad(lat2)) *
               std::sin(dLon/2) * std::sin(dLon/2);
    
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1-a));
    return EARTH_RADIUS_KM * c;
}

// Structure to represent a GPS coordinate
struct Coordinate {
    double lat;
    double lon;
    
    Coordinate() : lat(0.0), lon(0.0) {}
    Coordinate(double latitude, double longitude) : lat(latitude), lon(longitude) {}
    
    bool operator==(const Coordinate& other) const {
        return std::abs(lat - other.lat) < 1e-6 && std::abs(lon - other.lon) < 1e-6;
    }
    
    bool operator<(const Coordinate& other) const {
        if (std::abs(lat - other.lat) > 1e-6) return lat < other.lat;
        return lon < other.lon;
    }
    
    std::string toString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(6) << "(" << lat << ", " << lon << ")";
        return oss.str();
    }
};

// Node class
class Node {
public:
    int id;
    Coordinate coord;
    std::string type;  // "intersection", "bus_stop", "metro_station", "road_point"
    std::string name;
    
    Node() : id(-1), type("intersection") {}
    Node(int nodeId, double lat, double lon, std::string nodeType = "intersection", std::string nodeName = "")
        : id(nodeId), coord(lat, lon), type(nodeType), name(nodeName) {}
};

// Edge class
class Edge {
public:
    int source;
    int destination;
    double distance;  // in km
    std::string transportMode;  // "car", "metro", "bus_bikolpo", "bus_uttara"
    double costPerKm;
    double speedKmh;
    bool bidirectional;
    
    Edge(int src, int dest, double dist, std::string mode = "car",
         double cost = 20.0, double speed = 30.0, bool bidir = true)
        : source(src), destination(dest), distance(dist), transportMode(mode),
          costPerKm(cost), speedKmh(speed), bidirectional(bidir) {}
    
    double getCost() const {
        return distance * costPerKm;
    }
    
    double getTimeMinutes() const {
        return speedKmh > 0 ? (distance / speedKmh) * 60.0 : 0.0;
    }
};

// Graph class
class Graph {
private:
    std::map<int, Node> nodes;
    std::map<int, std::vector<Edge>> adjacencyList;
    int nextNodeId;
    
public:
    Graph() : nextNodeId(0) {}
    
    int addNode(const Node& node) {
        int id = node.id >= 0 ? node.id : nextNodeId++;
        nodes[id] = node;
        if (node.id < 0) nodes[id].id = id;
        if (adjacencyList.find(id) == adjacencyList.end()) {
            adjacencyList[id] = std::vector<Edge>();
        }
        return id;
    }
    
    void addEdge(const Edge& edge) {
        if (nodes.find(edge.source) == nodes.end() || 
            nodes.find(edge.destination) == nodes.end()) {
            return; // Invalid edge
        }
        
        adjacencyList[edge.source].push_back(edge);
        
        if (edge.bidirectional) {
            Edge reverseEdge(edge.destination, edge.source, edge.distance,
                           edge.transportMode, edge.costPerKm, edge.speedKmh, false);
            adjacencyList[edge.destination].push_back(reverseEdge);
        }
    }
    
    const std::vector<Edge>& getNeighbors(int nodeId) const {
        static const std::vector<Edge> empty;
        auto it = adjacencyList.find(nodeId);
        return it != adjacencyList.end() ? it->second : empty;
    }
    
    const Node* getNode(int nodeId) const {
        auto it = nodes.find(nodeId);
        return it != nodes.end() ? &(it->second) : nullptr;
    }
    
    int findNearestNode(double lat, double lon) const {
        int nearestId = -1;
        double minDist = INF;
        
        for (const auto& pair : nodes) {
            double dist = haversineDistance(lat, lon, 
                                          pair.second.coord.lat, 
                                          pair.second.coord.lon);
            if (dist < minDist) {
                minDist = dist;
                nearestId = pair.first;
            }
        }
        
        return nearestId;
    }
    
    int getNodeCount() const { return nodes.size(); }
    int getEdgeCount() const { 
        int count = 0;
        for (const auto& pair : adjacencyList) {
            count += pair.second.size();
        }
        return count;
    }
    
    const std::map<int, Node>& getAllNodes() const { return nodes; }
};

// Dijkstra's algorithm result
struct DijkstraResult {
    std::map<int, double> distances;
    std::map<int, int> parents;
    std::vector<int> path;
    double totalDistance;
    
    DijkstraResult() : totalDistance(0.0) {}
};

// Priority queue element for Dijkstra
struct PQElement {
    double priority;
    int nodeId;
    
    PQElement(double p, int n) : priority(p), nodeId(n) {}
    
    bool operator>(const PQElement& other) const {
        return priority > other.priority;
    }
};

// Dijkstra's algorithm implementation
DijkstraResult dijkstra(const Graph& graph, int source, int destination, 
                        std::string optimizeCriteria = "distance") {
    DijkstraResult result;
    std::map<int, bool> visited;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> pq;
    
    // Initialize
    for (const auto& pair : graph.getAllNodes()) {
        result.distances[pair.first] = INF;
        result.parents[pair.first] = -1;
        visited[pair.first] = false;
    }
    
    result.distances[source] = 0.0;
    pq.push(PQElement(0.0, source));
    
    while (!pq.empty()) {
        PQElement current = pq.top();
        pq.pop();
        
        int u = current.nodeId;
        
        if (visited[u]) continue;
        visited[u] = true;
        
        if (u == destination) break;  // Found shortest path to destination
        
        const std::vector<Edge>& neighbors = graph.getNeighbors(u);
        for (const Edge& edge : neighbors) {
            int v = edge.destination;
            double weight = 0.0;
            
            // Choose weight based on optimization criteria
            if (optimizeCriteria == "distance") {
                weight = edge.distance;
            } else if (optimizeCriteria == "cost") {
                weight = edge.getCost();
            } else if (optimizeCriteria == "time") {
                weight = edge.getTimeMinutes();
            }
            
            double newDist = result.distances[u] + weight;
            
            if (newDist < result.distances[v]) {
                result.distances[v] = newDist;
                result.parents[v] = u;
                pq.push(PQElement(newDist, v));
            }
        }
    }
    
    // Reconstruct path
    if (result.distances[destination] != INF) {
        int current = destination;
        while (current != -1) {
            result.path.insert(result.path.begin(), current);
            current = result.parents[current];
        }
        result.totalDistance = result.distances[destination];
    }
    
    return result;
}

// Generate KML file
void generateKML(const std::vector<Coordinate>& coordinates, 
                 int problemNumber, const std::string& filename = "") {
    std::string fname = filename.empty() ? 
        "problem_" + std::to_string(problemNumber) + "_route.kml" : filename;
    
    std::ofstream kmlFile(fname);
    
    kmlFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    kmlFile << "<kml xmlns=\"http://earth.google.com/kml/2.1\">\n";
    kmlFile << "<Document>\n";
    kmlFile << "  <Placemark>\n";
    kmlFile << "    <name>Problem " << problemNumber << " Route</name>\n";
    kmlFile << "    <LineString>\n";
    kmlFile << "      <tessellate>1</tessellate>\n";
    kmlFile << "      <coordinates>\n";
    
    for (const auto& coord : coordinates) {
        kmlFile << "        " << std::fixed << std::setprecision(6) 
                << coord.lon << "," << coord.lat << ",0\n";
    }
    
    kmlFile << "      </coordinates>\n";
    kmlFile << "    </LineString>\n";
    kmlFile << "  </Placemark>\n";
    kmlFile << "</Document>\n";
    kmlFile << "</kml>\n";
    
    kmlFile.close();
    std::cout << "KML file saved: " << fname << std::endl;
}

#endif // GRAPH_UTILS_H
