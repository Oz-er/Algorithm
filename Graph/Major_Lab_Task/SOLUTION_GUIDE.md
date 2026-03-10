# Dhaka Graph Assignment - Complete Solution Guide

## Overview
This project implements a multi-modal transportation routing system for Dhaka city using graph algorithms.

## Problem Analysis & Approach

### Core Concepts
- **Graph Representation**: Road network as weighted graph
- **Nodes**: Intersections, bus stops, metro stations, source/destination points
- **Edges**: Roads, bus routes, metro routes, walking paths
- **Weights**: Distance, cost, or time depending on optimization goal

### Key Algorithms
1. **Dijkstra's Algorithm** - For shortest path problems (distance, cost)
2. **Modified Dijkstra/A*** - For time-constrained problems with schedules
3. **Haversine Formula** - Calculate distance between GPS coordinates

---

## Problem Solutions

### Problem 1: Shortest Distance Car Route (2 marks)
**Objective**: Find minimum distance path using only roads (car)

**Algorithm**: Dijkstra's algorithm with distance as weight
**Steps**:
1. Parse `Roadmap-Dhaka.csv` into graph
2. Handle special cases (off-road points → walk to nearest road)
3. Run Dijkstra from source to destination
4. Output path coordinates

**Key Considerations**:
- Edge weight = distance in km
- Handle points in middle of road segments
- Walking speed: 2km/h (no cost)

---

### Problem 2: Cheapest Route (Car + Metro) (8 marks)
**Objective**: Minimize cost using car (৳20/km) and metro (৳5/km)

**Algorithm**: Dijkstra with cost as weight
**Steps**:
1. Build combined graph (roads + metro routes)
2. Edge weights = distance × cost per km
3. Run Dijkstra to minimize total cost
4. Allow mode switching at intersection/station nodes

**Cost Calculation**:
- Car: distance × 20
- Metro: distance × 5

---

### Problem 3: Cheapest Route (Car + Metro + Bus) (12 marks)
**Objective**: Minimize cost with all transport modes

**Transport Costs**:
- Car: ৳20/km
- Metro: ৳5/km  
- Bus: ৳7/km

**Algorithm**: Same as Problem 2 but with additional bus routes
**Steps**:
1. Parse all CSV files (roads, metro, both bus routes)
2. Build unified graph with all edges
3. Apply Dijkstra with cost weights
4. Track mode changes in the path

---

### Problem 4: Cheapest Route with Time Constraints (18 marks)
**Objective**: Minimize cost considering schedules and starting time

**New Constraints**:
- Speed: 30km/h (all vehicles)
- Bus/Metro: Every 15 minutes (6 AM - 11 PM)
- Starting time matters

**Algorithm**: Time-dependent Dijkstra
**Steps**:
1. State = (node, current_time)
2. For bus/metro: add waiting time for next departure
3. Edge weight = cost (minimize this)
4. Track arrival times to enforce schedules

**Time Calculations**:
- Travel time = distance / 30
- Wait time = time until next departure (0, 15, 30, ... minutes)
- If outside schedule (before 6 AM or after 11 PM), can't use bus/metro

---

### Problem 5: Fastest Route with Time Constraints (20 marks)
**Objective**: Minimize travel time (not cost)

**Constraints**:
- Speed: 10km/h (all vehicles)
- Bus/Metro: Every 15 minutes (6 AM - 11 PM)

**Algorithm**: Time-dependent Dijkstra with time as weight
**Steps**:
1. State = (node, current_time)
2. Edge weight = travel_time + waiting_time
3. Minimize total time to destination
4. Track which mode gives fastest arrival

**Key Difference from Problem 4**: Optimize time instead of cost

---

### Problem 6: Cheapest with Appointment Deadline (40 marks)
**Objective**: Minimize cost while arriving before deadline

**Complex Constraints**:
- Different costs: Car ৳20/km, Metro ৳5/km, Bikolpo ৳7/km, Uttara ৳10/km
- Different speeds: Car 20km/h, Metro 15km/h, Bikolpo 10km/h, Uttara 12km/h
- Different schedules:
  - Bikolpo: Every 20 min (7 AM - 10 PM)
  - Uttara: Every 10 min (6 AM - 11 PM)
  - Metro: Every 5 min (1 AM - 11 PM)

**Algorithm**: Constrained time-dependent Dijkstra
**Steps**:
1. State = (node, arrival_time, cost)
2. Prune paths that exceed deadline
3. Among valid paths, choose minimum cost
4. Handle different schedules per transport mode

**Strategy**:
- First filter by time feasibility
- Then minimize cost among feasible solutions
- Track mode-specific schedules carefully

---

## Implementation Guide

### Data Structures

```python
class Node:
    - id (lat, lon)
    - type (intersection, bus_stop, metro_station)
    - name (optional)

class Edge:
    - source_node
    - destination_node
    - distance (km)
    - transport_mode (car/metro/bus_bikolpo/bus_uttara)
    - cost_per_km
    - speed (km/h)

class Graph:
    - nodes: dict
    - edges: adjacency list
    - add_node()
    - add_edge()
    - get_neighbors()
```

### CSV Parsing

**Roadmap-Dhaka.csv**:
```
DhakaStreet, lon1,lat1,lon2,lat2,..., 0, distance_km
```

**Routemap-*.csv**:
```
TransportType, lon1,lat1,lon2,lat2,..., StartName, EndName
```

### Helper Functions

1. **haversine_distance(lat1, lon1, lat2, lon2)**: Calculate distance between GPS points
2. **find_nearest_node(point, graph)**: For off-road points
3. **is_on_segment(point, segment)**: Check if point on road segment
4. **calculate_wait_time(current_time, schedule)**: Time until next departure
5. **generate_kml(path_coordinates)**: Create KML file for visualization

### Dijkstra Implementation

```python
def dijkstra(graph, source, destination, weight_function):
    # priority queue: (weight, node, path, state)
    # visited set
    # while queue not empty:
    #   - pop minimum weight node
    #   - if destination: return path
    #   - for each neighbor: calculate new weight, add to queue
```

### Time-Dependent Dijkstra

```python
def time_dijkstra(graph, source, destination, start_time, optimize='cost'):
    # State: (node, current_time)
    # priority queue: (weight, node, time, path, cost)
    # Consider schedules when using bus/metro
    # Add waiting time to state transitions
```

---

## Output Format

### Text Output Template
```
Problem No: X
Source: (lon, lat)
Destination: (lon, lat)
Starting time at source: HH:MM AM/PM
Destination reaching time: HH:MM AM/PM
Total Cost: ৳XX.XX
Total Distance: XX.XX km
Total Time: XX minutes

HH:MM AM/PM - HH:MM AM/PM, Cost: ৳XX.XX: Mode from (lon,lat) to (lon,lat).
...
```

### KML File Template
```xml
<?xml version="1.0" encoding="UTF-8"?>
<kml xmlns="http://earth.google.com/kml/2.1">
<Document>
  <Placemark>
    <name>Problem X Route</name>
    <LineString>
      <tessellate>1</tessellate>
      <coordinates>
        lon1,lat1,0
        lon2,lat2,0
        ...
      </coordinates>
    </LineString>
  </Placemark>
</Document>
</kml>
```

---

## Testing Strategy

1. **Simple Cases**: Source and destination on same road
2. **Mode Switching**: Require changing between car/metro/bus
3. **Off-Road Points**: Test walking to nearest node
4. **Time Constraints**: Test schedule adherence
5. **Edge Cases**: 
   - Start before schedule begins
   - Can't reach before deadline
   - Multiple optimal paths

---

## Optimization Tips

1. **Use Priority Queue** (heapq in Python) for Dijkstra
2. **Cache distance calculations** between frequently used nodes
3. **Prune invalid paths early** in time-constrained problems
4. **Index nodes efficiently** (spatial hashing for nearest neighbor)
5. **Precompute schedules** as lookup tables

---

## Common Pitfalls

1. ❌ Forgetting to handle off-road points
2. ❌ Not accounting for waiting time at bus/metro stops
3. ❌ Mixing up lat/lon order (CSV uses lon,lat)
4. ❌ Not handling schedule boundaries (6 AM - 11 PM)
5. ❌ Forgetting mode-switch can only happen at valid nodes
6. ❌ Wrong distance calculations (use Haversine for GPS)
7. ❌ Not tracking full path for KML output

---

## Deliverables Checklist

- [ ] Solutions for all 6 problems
- [ ] Text descriptions with step-by-step directions
- [ ] KML files for each problem
- [ ] Code with clear documentation
- [ ] Test cases showing different scenarios
- [ ] Screenshots of routes on Google MyMaps

---

## Grading Rubric (Estimated)

| Problem | Marks | Key Criteria |
|---------|-------|--------------|
| 1 | 2 | Correct shortest path, handles 3 cases |
| 2 | 8 | Cost optimization, mode switching |
| 3 | 12 | Multi-modal routing, correct costs |
| 4 | 18 | Time-aware routing, schedule adherence |
| 5 | 20 | Time optimization, complex scheduling |
| 6 | 40 | Deadline constraint, different speeds/costs |

**Total: 100 marks**
