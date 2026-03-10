"""
CSV Data Parser for Dhaka Transportation Network
Parses the four CSV files into graph structure
"""

import csv
from typing import List, Tuple
from graph_utils import Graph, Node, Edge, parse_coordinate_list, haversine_distance


class DataParser:
    """Parse CSV files and build transportation graph"""
    
    def __init__(self):
        self.graph = Graph()
        self.metro_stops = {}  # name -> Node
        self.bus_stops = {}    # name -> Node
    
    def parse_roadmap(self, filepath: str):
        """
        Parse Roadmap-Dhaka.csv
        Format: DhakaStreet, lon1,lat1,lon2,lat2,..., 0, distance_km
        """
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                reader = csv.reader(f)
                for row in reader:
                    if len(row) < 4:
                        continue
                    
                    data_type = row[0].strip()
                    if data_type != "DhakaStreet":
                        continue
                    
                    # Extract coordinates
                    coord_string = row[1].strip()
                    coordinates = parse_coordinate_list(coord_string)
                    
                    # Distance is in the last column
                    total_distance = float(row[-1].strip())
                    
                    # Create nodes and edges for each segment
                    for i in range(len(coordinates) - 1):
                        lon1, lat1 = coordinates[i]
                        lon2, lat2 = coordinates[i + 1]
                        
                        node1 = Node(lon1, lat1, node_type="intersection")
                        node2 = Node(lon2, lat2, node_type="intersection")
                        
                        # Calculate segment distance
                        segment_dist = haversine_distance(lon1, lat1, lon2, lat2)
                        
                        # Add bidirectional road edge (car can use)
                        self.graph.add_bidirectional_edge(
                            node1, node2, segment_dist,
                            transport_mode="car",
                            cost_per_km=20,
                            speed_kmh=30
                        )
            
            print(f"✓ Parsed roadmap: {len(self.graph.nodes)} nodes, "
                  f"{sum(len(e) for e in self.graph.edges.values())} edges")
        
        except FileNotFoundError:
            print(f"⚠ Warning: {filepath} not found. Using empty road network.")
    
    def parse_metro_route(self, filepath: str):
        """
        Parse Routemap-DhakaMetroRail.csv
        Format: DhakaMetroRail, lon1,lat1,lon2,lat2,..., StartName, EndName
        """
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                reader = csv.reader(f)
                for row in reader:
                    if len(row) < 4:
                        continue
                    
                    transport_type = row[0].strip()
                    if transport_type != "DhakaMetroRail":
                        continue
                    
                    # Extract coordinates
                    coord_string = row[1].strip()
                    coordinates = parse_coordinate_list(coord_string)
                    
                    start_name = row[2].strip()
                    end_name = row[3].strip()
                    
                    # Create metro station nodes
                    for i, (lon, lat) in enumerate(coordinates):
                        station_name = start_name if i == 0 else (end_name if i == len(coordinates)-1 else f"Metro_{i}")
                        node = Node(lon, lat, node_type="metro_station", name=station_name)
                        self.graph.add_node(node)
                        self.metro_stops[station_name] = node
                    
                    # Create metro edges between consecutive stations
                    for i in range(len(coordinates) - 1):
                        lon1, lat1 = coordinates[i]
                        lon2, lat2 = coordinates[i + 1]
                        
                        node1 = self.graph.get_node(f"{lon1:.6f},{lat1:.6f}")
                        node2 = self.graph.get_node(f"{lon2:.6f},{lat2:.6f}")
                        
                        if node1 and node2:
                            distance = haversine_distance(lon1, lat1, lon2, lat2)
                            
                            # Add metro edge (bidirectional)
                            self.graph.add_bidirectional_edge(
                                node1, node2, distance,
                                transport_mode="metro",
                                cost_per_km=5,
                                speed_kmh=30
                            )
            
            print(f"✓ Parsed metro routes: {len(self.metro_stops)} stations")
        
        except FileNotFoundError:
            print(f"⚠ Warning: {filepath} not found. No metro routes added.")
    
    def parse_bus_route(self, filepath: str, bus_name: str = "bus"):
        """
        Parse bus route CSV
        Format: BusType, lon1,lat1,lon2,lat2,..., StartName, EndName
        """
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                reader = csv.reader(f)
                for row in reader:
                    if len(row) < 4:
                        continue
                    
                    transport_type = row[0].strip()
                    
                    # Extract coordinates
                    coord_string = row[1].strip()
                    coordinates = parse_coordinate_list(coord_string)
                    
                    start_name = row[2].strip()
                    end_name = row[3].strip()
                    
                    # Create bus stop nodes
                    for i, (lon, lat) in enumerate(coordinates):
                        stop_name = start_name if i == 0 else (end_name if i == len(coordinates)-1 else f"{bus_name}_{i}")
                        node = Node(lon, lat, node_type="bus_stop", name=stop_name)
                        self.graph.add_node(node)
                        self.bus_stops[f"{bus_name}_{stop_name}"] = node
                    
                    # Create bus edges between consecutive stops
                    for i in range(len(coordinates) - 1):
                        lon1, lat1 = coordinates[i]
                        lon2, lat2 = coordinates[i + 1]
                        
                        node1 = self.graph.get_node(f"{lon1:.6f},{lat1:.6f}")
                        node2 = self.graph.get_node(f"{lon2:.6f},{lat2:.6f}")
                        
                        if node1 and node2:
                            distance = haversine_distance(lon1, lat1, lon2, lat2)
                            
                            # Add bus edge (bidirectional)
                            self.graph.add_bidirectional_edge(
                                node1, node2, distance,
                                transport_mode=bus_name,
                                cost_per_km=7,
                                speed_kmh=30
                            )
            
            print(f"✓ Parsed {bus_name} routes: {len([k for k in self.bus_stops if bus_name in k])} stops")
        
        except FileNotFoundError:
            print(f"⚠ Warning: {filepath} not found. No {bus_name} routes added.")
    
    def load_all_data(self, roadmap_file: str = "Roadmap-Dhaka.csv",
                      metro_file: str = "Routemap-DhakaMetroRail.csv",
                      bikolpo_file: str = "Routemap-BikolpoBus.csv",
                      uttara_file: str = "Routemap-UttaraBus.csv"):
        """Load all CSV files into the graph"""
        print("Loading transportation network data...")
        
        self.parse_roadmap(roadmap_file)
        self.parse_metro_route(metro_file)
        self.parse_bus_route(bikolpo_file, "bikolpo_bus")
        self.parse_bus_route(uttara_file, "uttara_bus")
        
        print(f"\n✓ Total graph: {len(self.graph.nodes)} nodes, "
              f"{sum(len(e) for e in self.graph.edges.values())} edges")
        
        return self.graph


def create_sample_graph():
    """Create a small sample graph for testing when CSV files are not available"""
    graph = Graph()
    
    # Create sample nodes (Dhaka area)
    nodes = [
        Node(90.3563, 23.8103, name="Mirpur10", node_type="metro_station"),
        Node(90.3689, 23.8133, name="Mirpur11", node_type="metro_station"),
        Node(90.3792, 23.8163, name="Mirpur12", node_type="intersection"),
        Node(90.3913, 23.8223, name="Pallabi", node_type="bus_stop"),
        Node(90.4067, 23.8303, name="Uttara", node_type="metro_station"),
        Node(90.3856, 23.7808, name="Mohakhali", node_type="bus_stop"),
        Node(90.4125, 23.7908, name="Banani", node_type="intersection"),
        Node(90.4264, 23.8108, name="Gulshan", node_type="intersection"),
    ]
    
    for node in nodes:
        graph.add_node(node)
    
    # Add sample roads
    graph.add_bidirectional_edge(nodes[0], nodes[1], 1.5, "car", 20, 30)
    graph.add_bidirectional_edge(nodes[1], nodes[2], 1.2, "car", 20, 30)
    graph.add_bidirectional_edge(nodes[2], nodes[3], 0.8, "car", 20, 30)
    graph.add_bidirectional_edge(nodes[3], nodes[4], 2.1, "car", 20, 30)
    graph.add_bidirectional_edge(nodes[5], nodes[6], 1.4, "car", 20, 30)
    graph.add_bidirectional_edge(nodes[6], nodes[7], 1.8, "car", 20, 30)
    graph.add_bidirectional_edge(nodes[2], nodes[5], 3.5, "car", 20, 30)
    
    # Add metro lines
    graph.add_bidirectional_edge(nodes[0], nodes[1], 1.5, "metro", 5, 30)
    graph.add_bidirectional_edge(nodes[1], nodes[4], 3.2, "metro", 5, 30)
    
    # Add bus routes
    graph.add_bidirectional_edge(nodes[2], nodes[3], 0.8, "bikolpo_bus", 7, 30)
    graph.add_bidirectional_edge(nodes[3], nodes[5], 2.5, "uttara_bus", 10, 30)
    graph.add_bidirectional_edge(nodes[5], nodes[6], 1.4, "bikolpo_bus", 7, 30)
    
    print("✓ Created sample graph with 8 nodes")
    return graph


if __name__ == "__main__":
    # Test parser
    parser = DataParser()
    graph = parser.load_all_data()
    
    if len(graph.nodes) == 0:
        print("\nNo data loaded. Creating sample graph...")
        graph = create_sample_graph()
