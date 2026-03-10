# Dhaka Transportation Routing - C++ Solutions

## Overview
This directory contains C++ implementations for all 6 problems in the Dhaka Graph Assignment.

## Structure
```
cpp_solutions/
├── graph_utils.h          # Core graph data structures and Dijkstra implementation
├── csv_parser.h           # CSV file parser for loading datasets
├── time_utils.h           # Time-related utilities for Problems 4-6
├── problem1/              # Problem 1: Shortest distance car route
├── problem2/              # Problem 2: Cheapest route (Car + Metro)
├── problem3/              # Problem 3: Cheapest route (all modes)
├── problem4/              # Problem 4: Cheapest with time constraints
├── problem5/              # Problem 5: Fastest with time constraints
├── problem6/              # Problem 6: Cheapest with appointment deadline
├── Makefile               # Build configuration
└── README.md              # This file
```

## Prerequisites
- C++ compiler with C++11 support (g++ recommended)
- Make build tool
- Dataset CSV files in `../Route-de-Dhaka-master/Dataset/`

## Building the Solutions

### Build All Problems
```bash
make all
```

### Build Individual Problems
```bash
make problem1
make problem2
make problem3
make problem4
make problem5
make problem6
```

### Clean Build Files
```bash
make clean
```

## Running the Solutions

### Problem 1: Shortest Distance Car Route
```bash
./problem1/problem1
```
**Input**: Source and destination coordinates  
**Output**: Shortest distance path, KML file

### Problem 2: Cheapest Route (Car + Metro)
```bash
./problem2/problem2
```
**Costs**: Car ৳20/km, Metro ৳5/km  
**Output**: Minimum cost path, KML file

### Problem 3: Cheapest Route (All Modes)
```bash
./problem3/problem3
```
**Costs**: Car ৳20/km, Metro ৳5/km, Bus ৳7/km  
**Output**: Minimum cost path with mode switching, KML file

### Problem 4: Cheapest with Time Constraints
```bash
./problem4/problem4
```
**Input**: Source, destination, starting time  
**Speed**: 30km/h for all  
**Schedules**: Bus/Metro every 15 min (6 AM - 11 PM)  
**Output**: Cheapest time-aware route, KML file

### Problem 5: Fastest with Time Constraints
```bash
./problem5/problem5
```
**Input**: Source, destination, starting time  
**Speed**: 10km/h for all  
**Schedules**: Bus/Metro every 15 min (6 AM - 11 PM)  
**Output**: Fastest route, KML file

### Problem 6: Cheapest with Appointment Deadline
```bash
./problem6/problem6
```
**Input**: Source, destination, start time, deadline  
**Speeds**: Car 20km/h, Metro 15km/h, Bikolpo 10km/h, Uttara 12km/h  
**Costs**: Car ৳20/km, Metro ৳5/km, Bikolpo ৳7/km, Uttara ৳10/km  
**Schedules**: Varying by mode  
**Output**: Cheapest route arriving before deadline, KML file

## Input Format

### Coordinates
Enter latitude and longitude separated by space:
```
23.8103 90.3563
```

### Time (Problems 4-6)
Enter time in 12-hour format:
```
6:45 PM
```

### Exit
Enter `-1 -1` to exit any program.

## Output Files

Each problem generates:
1. **Console Output**: Detailed route instructions with costs/times
2. **KML File**: `problem_X_route.kml` for Google Maps visualization

## Viewing Routes on Google Maps

1. Go to https://www.google.com/mymaps
2. Click "CREATE A NEW MAP"
3. Click "Import"
4. Upload the generated KML file
5. View your route on the map!

## Algorithm Details

### Problem 1
- **Algorithm**: Dijkstra with distance weights
- **Complexity**: O((V + E) log V)

### Problems 2-3
- **Algorithm**: Dijkstra with cost weights
- **Features**: Multi-modal routing, mode switching at intersections

### Problems 4-6
- **Algorithm**: Time-dependent Dijkstra
- **Features**: Schedule adherence, waiting times, multiple vehicle speeds

## Key Features

✅ Haversine distance calculation for GPS coordinates  
✅ Multi-modal transportation support  
✅ Time-aware routing with schedules  
✅ KML generation for map visualization  
✅ Handles off-road points (walking to nearest node)  
✅ Bidirectional edges for roads  
✅ Cost and time optimization  

## Code Structure

### graph_utils.h
- `Coordinate`: GPS coordinate structure
- `Node`: Graph node with location and type
- `Edge`: Graph edge with mode, cost, speed
- `Graph`: Main graph class with adjacency list
- `dijkstra()`: Core pathfinding algorithm
- `generateKML()`: KML file generation

### csv_parser.h
- `CSVParser`: Loads all 4 CSV datasets
- Parses roads, metro routes, bus routes
- Creates unified graph structure

### time_utils.h
- `TransportSchedule`: Handles bus/metro schedules
- Time conversion utilities
- Schedule validation

## Notes

1. **Dataset Paths**: Update CSV file paths in code if needed
2. **Coordinate Format**: Uses (latitude, longitude) order
3. **Walking**: Assumed at 2 km/h with no cost
4. **Mode Switching**: Only at valid intersection nodes
5. **KML Coordinates**: Uses (longitude, latitude, altitude) format

## Troubleshooting

### "Error: No data loaded"
- Check that CSV files exist in `../Route-de-Dhaka-master/Dataset/`
- Verify file paths in code

### Compilation Errors
- Ensure C++11 support: `g++ -std=c++11`
- Check all header files are present

### No Path Found
- Verify source/destination coordinates are valid
- Check that graph is properly connected

## Example Session

```
Enter origin coordinates (lat lon) or -1 -1 to exit: 23.8103 90.3563
Enter destination coordinates (lat lon): 23.7808 90.3856

Calculating shortest path...
Total Distance: 4.523 km

========== PROBLEM 1 SOLUTION ==========
Source: (23.810300, 90.356300)
Destination: (23.780800, 90.385600)

Route Instructions:
----------------------------------------
Ride Car from (23.810300, 90.356300) to (23.803500, 90.365200)
Ride Car from (23.803500, 90.365200) to (23.795100, 90.375800)
Ride Car from (23.795100, 90.375800) to (23.780800, 90.385600)
========================================

KML file saved: problem_1_route.kml
```

## License
Academic use only - Code Samurai 2019 Problem Set

## Authors
C++ Implementation based on Python solutions from Route-de-Dhaka project
