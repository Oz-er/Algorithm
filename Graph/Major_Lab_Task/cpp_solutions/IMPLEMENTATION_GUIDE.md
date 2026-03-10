# C++ Solutions Implementation Guide

## Quick Start

### 1. Build All Solutions
```bash
cd cpp_solutions
make all
```

### 2. Run a Problem
```bash
./problem1/problem1
```

### 3. Example Input
```
Enter origin coordinates (lat lon): 23.8103 90.3563
Enter destination coordinates (lat lon): 23.7808 90.3856
```

## File Organization

### Core Headers (No compilation needed)
- **graph_utils.h** - Graph data structures, Dijkstra algorithm, KML generation
- **csv_parser.h** - Load CSV datasets into graph
- **time_utils.h** - Time/schedule utilities for Problems 4-6

### Problem Solutions (Compile to executables)
Each problem has its own folder with a .cpp file:
- problem1/problem1.cpp → Shortest distance
- problem2/problem2.cpp → Cheapest (Car + Metro)
- problem3/problem3.cpp → Cheapest (all modes)
- problem4/problem4.cpp → Cheapest with schedules
- problem5/problem5.cpp → Fastest with schedules  
- problem6/problem6.cpp → Cheapest with deadline

## Key Algorithms

### Dijkstra's Algorithm (All Problems)
```cpp
DijkstraResult dijkstra(const Graph& graph, 
                        int source, 
                        int destination, 
                        std::string criteria)
```
- **"distance"** → Minimize kilometers
- **"cost"** → Minimize money spent
- **"time"** → Minimize travel time

### Priority Queue Structure
```cpp
priority_queue<PQElement, vector<PQElement>, greater<PQElement>> pq;
```
Always picks the minimum weight node next (min-heap).

## Data Structures

### Coordinate
```cpp
struct Coordinate {
    double lat, lon;
};
```

### Node
```cpp
class Node {
    int id;
    Coordinate coord;
    string type;  // "intersection", "bus_stop", "metro_station"
    string name;
};
```

### Edge
```cpp
class Edge {
    int source, destination;
    double distance;          // km
    string transportMode;     // "car", "metro", "bikolpo_bus", "uttara_bus"
    double costPerKm;         // ৳/km
    double speedKmh;          // km/h
};
```

### Graph
```cpp
class Graph {
    map<int, Node> nodes;
    map<int, vector<Edge>> adjacencyList;
};
```

## Problem-Specific Logic

### Problem 1: Shortest Distance
```cpp
dijkstra(graph, source, dest, "distance");
```
Simple - just find shortest path using distance as weight.

### Problem 2 & 3: Cheapest Route
```cpp
dijkstra(graph, source, dest, "cost");
```
Edge weight = distance × costPerKm  
Graph includes: roads (car), metro, buses

### Problems 4-6: Time-Aware Routing
These require handling:
1. **Vehicle speeds** - Different modes travel at different speeds
2. **Schedules** - Bus/metro only available at certain times
3. **Waiting times** - May need to wait for next departure

```cpp
// Schedule example
TransportSchedule metroSchedule(15, 6, 23);  // Every 15 min, 6 AM - 11 PM
int waitTime = metroSchedule.getWaitTime(currentMinutes);
```

## CSV File Format

### Roadmap-Dhaka.csv
```
DhakaStreet, lon1,lat1,lon2,lat2,..., 0, distance_km
```

### Routemap-*.csv (Metro/Bus)
```
TransportType, lon1,lat1,lon2,lat2,..., StartName, EndName
```

## KML Generation

```cpp
generateKML(coordinates, problemNumber, "output.kml");
```

Creates a KML file you can upload to Google MyMaps to visualize the route.

## Compilation Commands

### Manual Compilation (if not using Makefile)
```bash
# Problem 1
g++ -std=c++11 -O2 -I. -o problem1/problem1 problem1/problem1.cpp -lm

# Problem 2
g++ -std=c++11 -O2 -I. -o problem2/problem2 problem2/problem2.cpp -lm

# And so on...
```

## Common Functions

### Haversine Distance
```cpp
double dist = haversineDistance(lat1, lon1, lat2, lon2);
```
Calculates distance in kilometers between two GPS coordinates.

### Find Nearest Node
```cpp
int nearestNode = graph.findNearestNode(lat, lon);
```
Finds closest node in graph to given coordinates.

### Get Path Coordinates
```cpp
vector<Coordinate> coords;
for (int nodeId : path) {
    const Node* node = graph.getNode(nodeId);
    if (node) coords.push_back(node->coord);
}
```

## Debugging Tips

### Print Graph Stats
```cpp
cout << "Nodes: " << graph.getNodeCount() << endl;
cout << "Edges: " << graph.getEdgeCount() << endl;
```

### Check if Path Found
```cpp
if (result.path.empty()) {
    cout << "No path found!" << endl;
}
```

### Verify Edge Weights
```cpp
for (const Edge& e : graph.getNeighbors(nodeId)) {
    cout << "To " << e.destination 
         << " dist=" << e.distance 
         << " cost=" << e.getCost() << endl;
}
```

## Output Example

```
========== PROBLEM 2 SOLUTION ==========
Source: (23.810300, 90.356300)
Destination: (23.780800, 90.385600)

Route Instructions:
----------------------------------------
Cost: ৳9.23: Ride Car from (23.810300, 90.356300) to (23.805200, 90.362100) (0.461 km)
Cost: ৳3.87: Ride Metro from (23.805200, 90.362100) to (23.795100, 90.375800) (0.774 km)
Cost: ৳12.56: Ride Car from (23.795100, 90.375800) to (23.780800, 90.385600) (0.628 km)
----------------------------------------
Total Cost: ৳25.66
Total Distance: 1.863 km
========================================
```

## Performance

- **Graph Construction**: O(E) where E = number of edges
- **Dijkstra**: O((V + E) log V) where V = nodes, E = edges
- **Typical Dhaka Graph**: ~1000 nodes, ~2000 edges
- **Execution Time**: < 1 second per query

## Extending the Solutions

### Add New Transport Mode
1. Add edges with new mode name in CSVParser
2. Update cost/speed in Edge constructor
3. Update output display to show new mode

### Add New Optimization Criteria
1. Add case in dijkstra() for new criteria
2. Calculate appropriate edge weight
3. Update PQElement comparison if needed

### Add Time Windows
1. Extend TransportSchedule class
2. Filter edges based on current time in dijkstra()
3. Track arrival time in path reconstruction

## Testing

### Test Cases
1. **Same source/dest** - Should return empty or single-node path
2. **Off-road points** - Should walk to nearest node
3. **No path exists** - Should handle gracefully
4. **Multiple modes** - Should switch at intersection nodes
5. **Schedule constraints** - Should respect operating hours

### Validation
- Total distance should match sum of edge distances
- Total cost should match sum of edge costs
- Path should be continuous (each edge connects)
- Times should be consistent with speeds

## Common Issues

### "No data loaded"
→ Check CSV file paths are correct

### "No path found"  
→ Source and destination might be in disconnected components

### Incorrect costs
→ Verify costPerKm values in Edge constructor

### Wrong coordinates in KML
→ Remember KML uses (lon, lat, alt) order, not (lat, lon)

## Resources

- **Dijkstra Algorithm**: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
- **Haversine Formula**: https://en.wikipedia.org/wiki/Haversine_formula
- **KML Reference**: https://developers.google.com/kml/documentation
- **Google MyMaps**: https://www.google.com/mymaps

## Next Steps

1. ✅ Build all solutions: `make all`
2. ✅ Test each problem with sample inputs
3. ✅ Generate KML files
4. ✅ Visualize routes on Google MyMaps
5. ✅ Compare results with Python solutions
6. ✅ Optimize for your specific use cases
