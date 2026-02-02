#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // For setprecision

using namespace std;

struct Item {
    int id;
    double weight;
    double value;
};

// Comparator to sort by Value/Weight ratio descending
bool compareRatio(const Item& a, const Item& b) {
    double r1 = a.value / a.weight;
    double r2 = b.value / b.weight;
    return r1 > r2;
}

void solveFractionalKnapsack(vector<Item>& items, double capacity) {
    // 1. Sort by density (value per unit weight)
    sort(items.begin(), items.end(), compareRatio);

    double totalValue = 0.0;
    double currentWeight = 0.0;

    cout << fixed << setprecision(2); // Format output

    for (const auto& item : items) {
        // If the item fits entirely
        if (currentWeight + item.weight <= capacity) {
            currentWeight += item.weight;
            totalValue += item.value;
            cout << "Took Item " << item.id << " (100%)" << endl;
        } 
        // If the item doesn't fit, take a fraction
        else {
            double remaining = capacity - currentWeight;
            double fraction = remaining / item.weight;
            
            totalValue += item.value * fraction;
            currentWeight += remaining; // Knapsack is full
            
            cout << "Took Item " << item.id << " (" << fraction * 100 << "%)" << endl;
            break; // We are done
        }
    }

    cout << "Total Value: " << totalValue << endl;
}

int main() {
    double capacity = 50;
    // Example Input: {ID, Weight, Value}
    vector<Item> items = {
        {1, 10, 60}, {2, 20, 100}, {3, 30, 120}
    };

    cout << "--- Fractional Knapsack ---" << endl;
    solveFractionalKnapsack(items, capacity);

    return 0;
}