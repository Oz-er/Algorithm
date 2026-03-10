#!/bin/bash
# Quick Setup Script for Dhaka Transportation Routing C++ Solutions

echo "======================================"
echo "Dhaka Transportation Routing - Setup"
echo "======================================"
echo ""

# Check if we're in the right directory
if [ ! -f "Makefile" ]; then
    echo "❌ Error: Makefile not found."
    echo "   Please run this script from the cpp_solutions directory."
    exit 1
fi

echo "✓ Found Makefile"

# Check for g++ compiler
if ! command -v g++ &> /dev/null; then
    echo "❌ Error: g++ compiler not found."
    echo "   Please install g++ (e.g., sudo apt install g++ or xcode-select --install)"
    exit 1
fi

echo "✓ Found g++ compiler"

# Check for CSV data files
DATA_DIR="../Route-de-Dhaka-master/Dataset"
if [ ! -d "$DATA_DIR" ]; then
    echo "⚠️  Warning: Dataset directory not found at $DATA_DIR"
    echo "   Solutions will compile but may not run without data."
else
    echo "✓ Found dataset directory"
    
    # Check for required CSV files
    REQUIRED_FILES=(
        "Roadmap-Dhaka.csv"
        "Routemap-DhakaMetroRail.csv"
        "Routemap-BikolpoBus.csv"
        "Routemap-UttaraBus.csv"
    )
    
    MISSING_FILES=0
    for file in "${REQUIRED_FILES[@]}"; do
        if [ ! -f "$DATA_DIR/$file" ]; then
            echo "   ⚠️  Missing: $file"
            MISSING_FILES=$((MISSING_FILES + 1))
        fi
    done
    
    if [ $MISSING_FILES -eq 0 ]; then
        echo "✓ All required CSV files found"
    else
        echo "   ⚠️  $MISSING_FILES CSV file(s) missing"
    fi
fi

echo ""
echo "======================================"
echo "Building Solutions..."
echo "======================================"
echo ""

# Build all solutions
make all

if [ $? -eq 0 ]; then
    echo ""
    echo "======================================"
    echo "✅ Build Successful!"
    echo "======================================"
    echo ""
    echo "Available executables:"
    echo "  ./problem1/problem1  - Shortest distance car route"
    echo "  ./problem2/problem2  - Cheapest route (Car + Metro)"
    echo "  ./problem3/problem3  - Cheapest route (all modes)"
    echo ""
    echo "To run a solution, use:"
    echo "  ./problem1/problem1"
    echo ""
    echo "For help:"
    echo "  cat README.md"
    echo ""
else
    echo ""
    echo "======================================"
    echo "❌ Build Failed"
    echo "======================================"
    echo ""
    echo "Please check the error messages above."
    exit 1
fi
