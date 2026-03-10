"""
Graph utilities for Dhaka routing system
Contains data structures and helper functions
"""

import math
import csv
from typing import Tuple, List, Dict, Optional, Set
from datetime import datetime, timedelta
import heapq


def haversine_distance(lon1: float, lat1: float, lon2: float, lat2: float) -> float:
    """
    Calculate the great circle distance between two points on Earth
    Returns distance in kilometers
    """
    # Convert to radians
    lon1, lat1, lon2, lat2 = map(math.radians, [lon1, lat1, lon2, lat2])
    
    # Haversine formula
    dlon = lon2 - lon1
    dlat = lat2 - lat1
    a = math.sin(dlat/2)**2 + math.cos(lat1) * math.cos(lat2) * math.sin(dlon/2)**2
    c = 2 * math.asin(math.sqrt(a))
    
    # Radius of Earth in kilometers
    r = 6371
    return c * r


class Node:
    """Represents a node in the transportation graph"""
    
    def __init__(self, lon: float, lat: float, node_id: str = None, 
                 node_type: str = "intersection", name: str = None):
        self.lon = lon
        self.lat = lat
        self.id = node_id or f"{lon:.6f},{lat:.6f}"
        self.type = node_type  # intersection, bus_stop, metro_station
        self.name = name
    
    def __repr__(self):
        return f"Node({self.lon}, {self.lat}, {self.type})"
    
    def __eq__(self, other):
        if not isinstance(other, Node):
            return False
        return self.id == other.id
    
    def __hash__(self):
        return hash(self.id)


class Edge:
    """Represents an edge in the transportation graph"""
    
    def __init__(self, source: Node, destination: Node, distance: float,
                 transport_mode: str = "car", cost_per_km: float = 20,
                 speed_kmh: float = 30):
        self.source = source
        self.destination = destination
        self.distance = distance  # in km
        self.transport_mode = transport_mode
        self.cost_per_km = cost_per_km
        self.speed_kmh = speed_kmh
        self.cost = distance * cost_per_km
        self.time_minutes = (distance / speed_kmh) * 60 if speed_kmh > 0 else 0
    
    def __repr__(self):
        return f"Edge({self.source.id} -> {self.destination.id}, " \
               f"{self.transport_mode}, {self.distance:.3f}km)"


class Graph:
    """Transportation graph for Dhaka routing"""
    
    def __init__(self):
        self.nodes: Dict[str, Node] = {}
        self.edges: Dict[str, List[Edge]] = {}  # adjacency list
        self.node_list: List[Node] = []
    
    def add_node(self, node: Node):
        """Add a node to the graph"""
        if node.id not in self.nodes:
            self.nodes[node.id] = node
            self.node_list.append(node)
            self.edges[node.id] = []
    
    def add_edge(self, edge: Edge):
        """Add an edge to the graph"""
        # Ensure nodes exist
        self.add_node(edge.source)
        self.add_node(edge.destination)
        
        # Add edge to adjacency list
        self.edges[edge.source.id].append(edge)
    
    def add_bidirectional_edge(self, source: Node, dest: Node, distance: float,
                               transport_mode: str = "car", cost_per_km: float = 20,
                               speed_kmh: float = 30):
        """Add edges in both directions"""
        edge1 = Edge(source, dest, distance, transport_mode, cost_per_km, speed_kmh)
        edge2 = Edge(dest, source, distance, transport_mode, cost_per_km, speed_kmh)
        self.add_edge(edge1)
        self.add_edge(edge2)
    
    def get_neighbors(self, node: Node) -> List[Edge]:
        """Get all outgoing edges from a node"""
        return self.edges.get(node.id, [])
    
    def get_node(self, node_id: str) -> Optional[Node]:
        """Get node by ID"""
        return self.nodes.get(node_id)
    
    def find_nearest_node(self, lon: float, lat: float, 
                         node_types: List[str] = None) -> Tuple[Node, float]:
        """
        Find the nearest node to given coordinates
        Returns (nearest_node, distance_km)
        """
        min_dist = float('inf')
        nearest = None
        
        for node in self.node_list:
            if node_types and node.type not in node_types:
                continue
            
            dist = haversine_distance(lon, lat, node.lon, node.lat)
            if dist < min_dist:
                min_dist = dist
                nearest = node
        
        return nearest, min_dist


class TransportSchedule:
    """Handles transport schedules for time-dependent routing"""
    
    def __init__(self, interval_minutes: int, start_hour: int, end_hour: int):
        self.interval_minutes = interval_minutes
        self.start_time = start_hour * 60  # in minutes from midnight
        self.end_time = end_hour * 60
    
    def get_next_departure(self, current_time_minutes: int) -> Optional[int]:
        """
        Get next departure time in minutes from midnight
        Returns None if no service available
        """
        if current_time_minutes > self.end_time:
            return None  # Service ended
        
        if current_time_minutes < self.start_time:
            return self.start_time  # First departure
        
        # Calculate next departure
        time_since_start = current_time_minutes - self.start_time
        intervals_passed = time_since_start // self.interval_minutes
        next_departure = self.start_time + (intervals_passed + 1) * self.interval_minutes
        
        if next_departure > self.end_time:
            return None
        
        return next_departure
    
    def get_wait_time(self, current_time_minutes: int) -> Optional[int]:
        """Get waiting time in minutes until next departure"""
        next_dep = self.get_next_departure(current_time_minutes)
        if next_dep is None:
            return None
        return next_dep - current_time_minutes


def time_to_minutes(time_str: str) -> int:
    """Convert time string (e.g., '5:43 PM') to minutes from midnight"""
    time_obj = datetime.strptime(time_str, "%I:%M %p")
    return time_obj.hour * 60 + time_obj.minute


def minutes_to_time(minutes: int) -> str:
    """Convert minutes from midnight to time string"""
    hours = (minutes // 60) % 24
    mins = minutes % 60
    period = "AM" if hours < 12 else "PM"
    display_hour = hours if hours <= 12 else hours - 12
    if display_hour == 0:
        display_hour = 12
    return f"{display_hour}:{mins:02d} {period}"


def parse_coordinate_list(coord_str: str) -> List[Tuple[float, float]]:
    """
    Parse comma-separated coordinate string into list of (lon, lat) tuples
    Example: "90.363833, 23.834145, 90.363843, 23.834245" -> [(90.363833, 23.834145), ...]
    """
    coords = [float(x.strip()) for x in coord_str.split(',')]
    return [(coords[i], coords[i+1]) for i in range(0, len(coords), 2)]


def is_point_on_segment(point: Tuple[float, float], 
                        seg_start: Tuple[float, float],
                        seg_end: Tuple[float, float],
                        tolerance: float = 0.0001) -> bool:
    """
    Check if a point lies on a line segment
    Uses cross product to check collinearity
    """
    px, py = point
    x1, y1 = seg_start
    x2, y2 = seg_end
    
    # Check if point is within bounding box
    if not (min(x1, x2) - tolerance <= px <= max(x1, x2) + tolerance and
            min(y1, y2) - tolerance <= py <= max(y1, y2) + tolerance):
        return False
    
    # Check collinearity using cross product
    cross = abs((py - y1) * (x2 - x1) - (px - x1) * (y2 - y1))
    return cross < tolerance


def find_point_on_road_network(graph: Graph, lon: float, lat: float) -> Tuple[Node, float, bool]:
    """
    Find if point is on road network or needs walking
    Returns (node, distance_to_node, needs_walking)
    """
    # First check if point is exactly on a node
    for node in graph.node_list:
        dist = haversine_distance(lon, lat, node.lon, node.lat)
        if dist < 0.001:  # Within 1 meter
            return node, 0.0, False
    
    # Check if point is on any edge (middle of road)
    for node_id, edges in graph.edges.items():
        for edge in edges:
            if is_point_on_segment((lon, lat), 
                                  (edge.source.lon, edge.source.lat),
                                  (edge.destination.lon, edge.destination.lat)):
                # Create new node at this point
                new_node = Node(lon, lat, node_type="road_point")
                return new_node, 0.0, False
    
    # Point is off-road, find nearest node
    nearest_node, distance = graph.find_nearest_node(lon, lat)
    return nearest_node, distance, True


def generate_kml(path_coordinates: List[Tuple[float, float]], 
                 problem_number: int,
                 filename: str = None) -> str:
    """Generate KML file content for route visualization"""
    if filename is None:
        filename = f"problem_{problem_number}_route.kml"
    
    coords_str = "\n        ".join([f"{lon},{lat},0" for lon, lat in path_coordinates])
    
    kml_content = f"""<?xml version="1.0" encoding="UTF-8"?>
<kml xmlns="http://earth.google.com/kml/2.1">
<Document>
  <Placemark>
    <name>Problem {problem_number} Route</name>
    <LineString>
      <tessellate>1</tessellate>
      <coordinates>
        {coords_str}
      </coordinates>
    </LineString>
  </Placemark>
</Document>
</kml>"""
    
    return kml_content


def save_kml(path_coordinates: List[Tuple[float, float]], 
             problem_number: int,
             output_dir: str = "."):
    """Save KML file to disk"""
    filename = f"{output_dir}/problem_{problem_number}_route.kml"
    content = generate_kml(path_coordinates, problem_number)
    
    with open(filename, 'w', encoding='utf-8') as f:
        f.write(content)
    
    return filename
