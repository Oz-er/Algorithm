/*
 * Problem 1: Shortest Distance Car Route
 * 
 * Objective: Find the shortest distance path using only car (roads)
 * Input: Source and destination coordinates
 * Output: Shortest path in KML format and text description
 * 
 * Algorithm: Dijkstra's algorithm with distance as weight
 * Marks: 2
 */

#include "../graph_utils.h"
#include "../csv_parser.h"
#include <iostream>
#include <iomanip>

void printPathInfo(const Graph& graph, const std::vector<int>& path, 
                   const Coordinate& source, const Coordinate& dest,
                   bool sameSource, bool sameDest) {
    std::cout << "\n========== PROBLEM 1 SOLUTION ==========\n";
    std::cout << "Source: " << source.toString() << std::endl;
    std::cout << "Destination: " << dest.toString() << std::endl;
    std::cout << "\nRoute Instructions:\n";
    std::cout << "----------------------------------------\n";
    
    if (!sameSource) {
        std::cout << "Walk from Source " << source.toString();
        const Node* firstNode = graph.getNode(path[0]);
        if (firstNode) {
            std::cout << " to " << firstNode->coord.toString() << std::endl;
        }
    }
    
    for (size_t i = 0; i + 1 < path.size(); i++) {
        const Node* node1 = graph.getNode(path[i]);
        const Node* node2 = graph.getNode(path[i + 1]);
        
        if (node1 && node2) {
            std::cout << "Ride Car from " << node1->coord.toString()
                     << " to " << node2->coord.toString() << std::endl;
        }
    }
    
    if (!sameDest) {
        const Node* lastNode = graph.getNode(path[path.size() - 1]);
        if (lastNode) {
            std::cout << "Walk from " << lastNode->coord.toString()
                     << " to Destination " << dest.toString() << std::endl;
        }
    }
    
    std::cout << "========================================\n";
}

std::vector<Coordinate> getPathCoordinates(const Graph& graph, 
                                           const std::vector<int>& path,
                                           const Coordinate& source,
                                           const Coordinate& dest,
                                           bool sameSource, bool sameDest) {
    std::vector<Coordinate> coords;
    
    if (!sameSource) {
        coords.push_back(source);
    }
    
    for (int nodeId : path) {
        const Node* node = graph.getNode(nodeId);
        if (node) {
            coords.push_back(node->coord);
        }
    }
    
    if (!sameDest) {
        coords.push_back(dest);
    }
    
    return coords;
}

int main() {
    // Create graph and load data
    Graph graph;
    CSVParser parser(graph);
    parser.loadAllData();
    
    if (graph.getNodeCount() == 0) {
        std::cerr << "Error: No data loaded. Please check CSV file paths." << std::endl;
        return 1;
    }
    
    std::cout << "\n========== PROBLEM 1: SHORTEST CAR ROUTE ==========\n\n";
    
    while (true) {
        double srcLat, srcLon, destLat, destLon;
        
        std::cout << "Enter origin coordinates (lat lon) or -1 -1 to exit: ";
        std::cin >> srcLat >> srcLon;
        
        if (srcLat == -1 && srcLon == -1) {
            std::cout << "Exiting..." << std::endl;
            break;
        }
        
        std::cout << "Enter destination coordinates (lat lon): ";
        std::cin >> destLat >> destLon;
        
        Coordinate source(srcLat, srcLon);
        Coordinate dest(destLat, destLon);
        
        // Find nearest nodes
        int sourceNode = graph.findNearestNode(srcLat, srcLon);
        int destNode = graph.findNearestNode(destLat, destLon);
        
        if (sourceNode == -1 || destNode == -1) {
            std::cerr << "Error: Could not find nearest nodes." << std::endl;
            continue;
        }
        
        const Node* srcNodePtr = graph.getNode(sourceNode);
        const Node* destNodePtr = graph.getNode(destNode);
        
        bool sameSource = (srcNodePtr && srcNodePtr->coord == source);
        bool sameDest = (destNodePtr && destNodePtr->coord == dest);
        
        std::cout << "\nCalculating shortest path..." << std::endl;
        
        // Run Dijkstra's algorithm
        DijkstraResult result = dijkstra(graph, sourceNode, destNode, "distance");
        
        if (result.path.empty()) {
            std::cout << "No path found between source and destination." << std::endl;
            continue;
        }
        
        std::cout << "Total Distance: " << std::fixed << std::setprecision(3) 
                  << result.totalDistance << " km" << std::endl;
        
        // Print path information
        printPathInfo(graph, result.path, source, dest, sameSource, sameDest);
        
        // Generate KML file
        std::vector<Coordinate> pathCoords = getPathCoordinates(
            graph, result.path, source, dest, sameSource, sameDest);
        
        generateKML(pathCoords, 1, "problem_1_route.kml");
        
        std::cout << "\n";
    }
    
    return 0;
}
