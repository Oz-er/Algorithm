# Makefile for Dhaka Transportation Routing C++ Solutions

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -I.
LDFLAGS = -lm

# Targets
PROBLEMS = problem1 problem2 problem3 problem4 problem5 problem6

.PHONY: all clean $(PROBLEMS)

all: $(PROBLEMS)

# Problem 1: Shortest distance car route
problem1: problem1/problem1.cpp graph_utils.h csv_parser.h
	@echo "Building Problem 1..."
	@mkdir -p problem1
	$(CXX) $(CXXFLAGS) -o problem1/problem1 problem1/problem1.cpp $(LDFLAGS)
	@echo "✓ Problem 1 built successfully"

# Problem 2: Cheapest route (Car + Metro)
problem2: problem2/problem2.cpp graph_utils.h csv_parser.h
	@echo "Building Problem 2..."
	@mkdir -p problem2
	$(CXX) $(CXXFLAGS) -o problem2/problem2 problem2/problem2.cpp $(LDFLAGS)
	@echo "✓ Problem 2 built successfully"

# Problem 3: Cheapest route (all modes)
problem3: problem3/problem3.cpp graph_utils.h csv_parser.h
	@echo "Building Problem 3..."
	@mkdir -p problem3
	$(CXX) $(CXXFLAGS) -o problem3/problem3 problem3/problem3.cpp $(LDFLAGS)
	@echo "✓ Problem 3 built successfully"

# Problem 4: Cheapest with time constraints
problem4: problem4/problem4.cpp graph_utils.h csv_parser.h time_utils.h
	@echo "Building Problem 4..."
	@mkdir -p problem4
	$(CXX) $(CXXFLAGS) -o problem4/problem4 problem4/problem4.cpp $(LDFLAGS)
	@echo "✓ Problem 4 built successfully"

# Problem 5: Fastest with time constraints
problem5: problem5/problem5.cpp graph_utils.h csv_parser.h time_utils.h
	@echo "Building Problem 5..."
	@mkdir -p problem5
	$(CXX) $(CXXFLAGS) -o problem5/problem5 problem5/problem5.cpp $(LDFLAGS)
	@echo "✓ Problem 5 built successfully"

# Problem 6: Cheapest with appointment deadline
problem6: problem6/problem6.cpp graph_utils.h csv_parser.h time_utils.h
	@echo "Building Problem 6..."
	@mkdir -p problem6
	$(CXX) $(CXXFLAGS) -o problem6/problem6 problem6/problem6.cpp $(LDFLAGS)
	@echo "✓ Problem 6 built successfully"

# Clean all build artifacts
clean:
	@echo "Cleaning build files..."
	@rm -f problem1/problem1
	@rm -f problem2/problem2
	@rm -f problem3/problem3
	@rm -f problem4/problem4
	@rm -f problem5/problem5
	@rm -f problem6/problem6
	@rm -f *.kml
	@rm -f problem*/*.kml
	@echo "✓ Clean complete"

# Help target
help:
	@echo "Dhaka Transportation Routing - Makefile"
	@echo ""
	@echo "Usage:"
	@echo "  make all       - Build all problems"
	@echo "  make problem1  - Build Problem 1 only"
	@echo "  make problem2  - Build Problem 2 only"
	@echo "  make problem3  - Build Problem 3 only"
	@echo "  make problem4  - Build Problem 4 only"
	@echo "  make problem5  - Build Problem 5 only"
	@echo "  make problem6  - Build Problem 6 only"
	@echo "  make clean     - Remove all build files"
	@echo "  make help      - Show this help message"
