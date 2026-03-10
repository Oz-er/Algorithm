/*
 * Problem 3: Cheapest Route (Car + Metro + Bus)
 * 
 * Objective: Find minimum cost path using all transport modes
 * Costs: Car ৳20/km, Metro ৳5/km, Bus ৳7/km
 * Output: Cheapest path with mode information
 * 
 * Algorithm: Dijkstra's algorithm with cost as weight
 * Marks: 12
 */

#include "../graph_utils.h"
#include "../csv_parser.h"
#include <iostream>
#include <iomanip>

void printPathInfoWithAllModes(const Graph& graph, const std::vector<int>& path, 
                               const Coordinate& source, const Coordinate& dest,
                               bool sameSource, bool sameDest) {
    std::cout << "\n========== PROBLEM 3 SOLUTION ==========\n";
    std::cout << "Source: " << source.toString() << std::endl;
    std::cout << "Destination: " << dest.toString() << std::endl;
    std::cout << "\nRoute Instructions:\n";
    std::cout << "----------------------------------------\n";
    
    double totalCost = 0.0;
    double totalDistance = 0.0;
    
    if (!sameSource) {
        const Node* firstNode = graph.getNode(path[0]);
        if (firstNode) {
            double walkDist = haversineDistance(source.lat, source.lon,
                                               firstNode->coord.lat, firstNode->coord.lon);
            std::cout << "Cost: ৳0.00: Walk from Source " << source.toString()
                     << " to " << firstNode->coord.toString()
                     << " (" << std::fixed << std::setprecision(3) << walkDist << " km)"
                     << std::endl;
        }
    }
    
    for (size_t i = 0; i + 1 < path.size(); i++) {
        const Node* node1 = graph.getNode(path[i]);
        const Node* node2 = graph.getNode(path[i + 1]);
        
        if (node1 && node2) {
            // Find the edge between these nodes to get the transport mode
            const std::vector<Edge>& edges = graph.getNeighbors(path[i]);
            double distance = 0.0;
            double cost = 0.0;
            std::string mode = "car";
            
            for (const Edge& edge : edges) {
                if (edge.destination == path[i + 1]) {
                    distance = edge.distance;
                    cost = edge.getCost();
                    mode = edge.transportMode;
                    break;
                }
            }
            
            totalCost += cost;
            totalDistance += distance;
            
            std::string modeDisplay;
            if (mode == "metro") modeDisplay = "Metro";
            else if (mode == "bikolpo_bus") modeDisplay = "Bikolpo Bus";
            else if (mode == "uttara_bus") modeDisplay = "Uttara Bus";
            else modeDisplay = "Car";
            
            std::cout << "Cost: ৳" << std::fixed << std::setprecision(2) << cost 
                     << ": Ride " << modeDisplay << " from " << node1->coord.toString()
                     << " to " << node2->coord.toString()
                     << " (" << std::fixed << std::setprecision(3) << distance << " km)"
                     << std::endl;
        }
    }
    
    if (!sameDest) {
        const Node* lastNode = graph.getNode(path[path.size() - 1]);
        if (lastNode) {
            double walkDist = haversineDistance(lastNode->coord.lat, lastNode->coord.lon,
                                               dest.lat, dest.lon);
            std::cout << "Cost: ৳0.00: Walk from " << lastNode->coord.toString()
                     << " to Destination " << dest.toString()
                     << " (" << std::fixed << std::setprecision(3) << walkDist << " km)"
                     << std::endl;
        }
    }
    
    std::cout << "----------------------------------------\n";
    std::cout << "Total Cost: ৳" << std::fixed << std::setprecision(2) << totalCost << std::endl;
    std::cout << "Total Distance: " << std::fixed << std::setprecision(3) << totalDistance << " km" << std::endl;
    std::cout << "========================================\n";
}

int main() {
    // Create graph and load all data
    Graph graph;
    CSVParser parser(graph);
    parser.loadAllData();
    
    if (graph.getNodeCount() == 0) {
        std::cerr << "Error: No data loaded. Please check CSV file paths." << std::endl;
        return 1;
    }
    
    std::cout << "\n========== PROBLEM 3: CHEAPEST ROUTE (ALL MODES) ==========\n\n";
    std::cout << "Cost Information:\n";
    std::cout << "  Car:   ৳20/km\n";
    std::cout << "  Metro: ৳5/km\n";
    std::cout << "  Bus:   ৳7/km\n\n";
    
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
        
        std::cout << "\nCalculating cheapest path..." << std::endl;
        
        // Run Dijkstra's algorithm with cost optimization
        DijkstraResult result = dijkstra(graph, sourceNode, destNode, "cost");
        
        if (result.path.empty()) {
            std::cout << "No path found between source and destination." << std::endl;
            continue;
        }
        
        // Print path information with costs
        printPathInfoWithAllModes(graph, result.path, source, dest, sameSource, sameDest);
        
        // Generate KML file
        std::vector<Coordinate> pathCoords;
        if (!sameSource) pathCoords.push_back(source);
        for (int nodeId : result.path) {
            const Node* node = graph.getNode(nodeId);
            if (node) pathCoords.push_back(node->coord);
        }
        if (!sameDest) pathCoords.push_back(dest);
        
        generateKML(pathCoords, 3, "problem_3_route.kml");
        
        std::cout << "\n";
    }
    
    return 0;
}
