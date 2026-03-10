#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "graph_utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

class CSVParser {
private:
    Graph& graph;
    std::map<Coordinate, int> coordToNode;
    
    // Helper function to split string by delimiter
    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        
        while (std::getline(ss, token, delimiter)) {
            // Trim whitespace
            token.erase(0, token.find_first_not_of(" \t\r\n"));
            token.erase(token.find_last_not_of(" \t\r\n") + 1);
            tokens.push_back(token);
        }
        
        return tokens;
    }
    
    // Get or create node for a coordinate
    int getOrCreateNode(double lat, double lon, std::string type = "intersection", 
                       std::string name = "") {
        Coordinate coord(lat, lon);
        
        auto it = coordToNode.find(coord);
        if (it != coordToNode.end()) {
            return it->second;
        }
        
        Node node(-1, lat, lon, type, name);
        int id = graph.addNode(node);
        coordToNode[coord] = id;
        return id;
    }
    
public:
    CSVParser(Graph& g) : graph(g) {}
    
    // Parse Roadmap-Dhaka.csv
    bool parseRoadmap(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Warning: Could not open " << filepath << std::endl;
            return false;
        }
        
        std::string line;
        int edgeCount = 0;
        
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            std::vector<std::string> tokens = split(line, ',');
            if (tokens.size() < 4) continue;
            
            std::string dataType = tokens[0];
            if (dataType != "DhakaStreet") continue;
            
            // Extract coordinates (skip first token which is data type)
            std::vector<double> coords;
            for (size_t i = 1; i < tokens.size() - 1; i++) {  // -1 to skip distance at end
                try {
                    double val = std::stod(tokens[i]);
                    coords.push_back(val);
                } catch (...) {
                    break;  // Stop when we hit non-numeric data
                }
            }
            
            // Create nodes and edges
            for (size_t i = 0; i + 3 < coords.size(); i += 2) {
                double lon1 = coords[i];
                double lat1 = coords[i + 1];
                double lon2 = coords[i + 2];
                double lat2 = coords[i + 3];
                
                int node1 = getOrCreateNode(lat1, lon1, "intersection");
                int node2 = getOrCreateNode(lat2, lon2, "intersection");
                
                double distance = haversineDistance(lat1, lon1, lat2, lon2);
                
                Edge edge(node1, node2, distance, "car", 20.0, 30.0, true);
                graph.addEdge(edge);
                edgeCount++;
            }
        }
        
        file.close();
        std::cout << "✓ Parsed roadmap: " << graph.getNodeCount() << " nodes, " 
                  << graph.getEdgeCount() << " edges" << std::endl;
        return true;
    }
    
    // Parse metro route CSV
    bool parseMetroRoute(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Warning: Could not open " << filepath << std::endl;
            return false;
        }
        
        std::string line;
        int stationCount = 0;
        
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            std::vector<std::string> tokens = split(line, ',');
            if (tokens.size() < 4) continue;
            
            std::string transportType = tokens[0];
            if (transportType != "DhakaMetroRail") continue;
            
            // Extract coordinates
            std::vector<double> coords;
            size_t i = 1;
            for (; i < tokens.size() - 2; i++) {  // -2 to skip start and end names
                try {
                    double val = std::stod(tokens[i]);
                    coords.push_back(val);
                } catch (...) {
                    break;
                }
            }
            
            std::string startName = tokens[tokens.size() - 2];
            std::string endName = tokens[tokens.size() - 1];
            
            // Create metro station nodes and edges
            std::vector<int> stationNodes;
            for (size_t j = 0; j + 1 < coords.size(); j += 2) {
                double lon = coords[j];
                double lat = coords[j + 1];
                std::string name = (j == 0) ? startName : 
                                   (j + 2 >= coords.size()) ? endName : 
                                   "Metro_" + std::to_string(j/2);
                
                int node = getOrCreateNode(lat, lon, "metro_station", name);
                stationNodes.push_back(node);
                stationCount++;
            }
            
            // Connect consecutive stations
            for (size_t j = 0; j + 1 < stationNodes.size(); j++) {
                const Node* n1 = graph.getNode(stationNodes[j]);
                const Node* n2 = graph.getNode(stationNodes[j + 1]);
                
                if (n1 && n2) {
                    double distance = haversineDistance(
                        n1->coord.lat, n1->coord.lon,
                        n2->coord.lat, n2->coord.lon
                    );
                    
                    Edge edge(stationNodes[j], stationNodes[j + 1], 
                             distance, "metro", 5.0, 30.0, true);
                    graph.addEdge(edge);
                }
            }
        }
        
        file.close();
        std::cout << "✓ Parsed metro routes: " << stationCount << " stations" << std::endl;
        return true;
    }
    
    // Parse bus route CSV
    bool parseBusRoute(const std::string& filepath, const std::string& busName) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Warning: Could not open " << filepath << std::endl;
            return false;
        }
        
        std::string line;
        int stopCount = 0;
        double costPerKm = (busName == "bikolpo_bus") ? 7.0 : 10.0;
        
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            std::vector<std::string> tokens = split(line, ',');
            if (tokens.size() < 4) continue;
            
            // Extract coordinates
            std::vector<double> coords;
            size_t i = 1;
            for (; i < tokens.size() - 2; i++) {
                try {
                    double val = std::stod(tokens[i]);
                    coords.push_back(val);
                } catch (...) {
                    break;
                }
            }
            
            std::string startName = tokens[tokens.size() - 2];
            std::string endName = tokens[tokens.size() - 1];
            
            // Create bus stop nodes and edges
            std::vector<int> stopNodes;
            for (size_t j = 0; j + 1 < coords.size(); j += 2) {
                double lon = coords[j];
                double lat = coords[j + 1];
                std::string name = (j == 0) ? startName : 
                                   (j + 2 >= coords.size()) ? endName : 
                                   busName + "_" + std::to_string(j/2);
                
                int node = getOrCreateNode(lat, lon, "bus_stop", name);
                stopNodes.push_back(node);
                stopCount++;
            }
            
            // Connect consecutive stops
            for (size_t j = 0; j + 1 < stopNodes.size(); j++) {
                const Node* n1 = graph.getNode(stopNodes[j]);
                const Node* n2 = graph.getNode(stopNodes[j + 1]);
                
                if (n1 && n2) {
                    double distance = haversineDistance(
                        n1->coord.lat, n1->coord.lon,
                        n2->coord.lat, n2->coord.lon
                    );
                    
                    Edge edge(stopNodes[j], stopNodes[j + 1], 
                             distance, busName, costPerKm, 30.0, true);
                    graph.addEdge(edge);
                }
            }
        }
        
        file.close();
        std::cout << "✓ Parsed " << busName << " routes: " << stopCount << " stops" << std::endl;
        return true;
    }
    
    // Load all data files
    void loadAllData(const std::string& roadmapFile = "../Route-de-Dhaka-master/Dataset/Roadmap-Dhaka.csv",
                     const std::string& metroFile = "../Route-de-Dhaka-master/Dataset/Routemap-DhakaMetroRail.csv",
                     const std::string& bikolpoFile = "../Route-de-Dhaka-master/Dataset/Routemap-BikolpoBus.csv",
                     const std::string& uttaraFile = "../Route-de-Dhaka-master/Dataset/Routemap-UttaraBus.csv") {
        std::cout << "Loading transportation network data..." << std::endl;
        
        parseRoadmap(roadmapFile);
        parseMetroRoute(metroFile);
        parseBusRoute(bikolpoFile, "bikolpo_bus");
        parseBusRoute(uttaraFile, "uttara_bus");
        
        std::cout << "\n✓ Total graph: " << graph.getNodeCount() << " nodes, " 
                  << graph.getEdgeCount() << " edges" << std::endl;
    }
};

#endif // CSV_PARSER_H
