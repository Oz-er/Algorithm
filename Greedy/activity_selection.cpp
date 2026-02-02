#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Activity {
    int id;
    int start;
    int finish;
};

// Comparator to sort activities by finish time
bool compareActivities(const Activity& a, const Activity& b) {
    return a.finish < b.finish;
}

void solveActivitySelection(vector<Activity>& activities) {
    // 1. Sort by finish time
    sort(activities.begin(), activities.end(), compareActivities);

    cout << "Selected Activities (ID): ";

    // 2. The first activity is always selected
    int last_finish_time = activities[0].finish;
    cout << activities[0].id << " ";

    // 3. Iterate through the rest
    for (size_t i = 1; i < activities.size(); i++) {
        // If this activity starts after or when the last one finished
        if (activities[i].start >= last_finish_time) {
            cout << activities[i].id << " ";
            last_finish_time = activities[i].finish;
        }
    }
    cout << endl;
}

int main() {
    // Example Input: {ID, Start, Finish}
    vector<Activity> activities = {
        {1, 5, 9}, {2, 1, 2}, {3, 3, 4}, 
        {4, 0, 6}, {5, 5, 7}, {6, 8, 9}
    };

    cout << "--- Activity Selection ---" << endl;
    solveActivitySelection(activities);
    return 0;
}