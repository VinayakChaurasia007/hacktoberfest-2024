#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const double INF = numeric_limits<double>::max();

// Function to find the minimum cost using dynamic programming
double tsp(int mask, int pos, const vector<vector<double>> &distances, vector<vector<double>> &dp) {
    // If all cities have been visited, return to the starting city
    if (mask == (1 << distances.size()) - 1) {
        return distances[pos][0]; // Return to starting city
    }

    // If the result is already computed, return it
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    double ans = INF; // Initialize with infinity

    // Explore all cities to find the minimum cost
    for (int city = 0; city < distances.size(); city++) {
        // If the city has not been visited
        if ((mask & (1 << city)) == 0) {
            double newCost = distances[pos][city] + tsp(mask | (1 << city), city, distances, dp);
            ans = min(ans, newCost); // Update the answer
        }
    }

    return dp[mask][pos] = ans; // Store the result in the DP table
}

int main() {
    int n; // Number of cities
    cout << "Enter the number of cities: ";
    cin >> n;

    vector<vector<double>> distances(n, vector<double>(n));
    cout << "Enter the distance matrix (0 for the same city):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> distances[i][j];
        }
    }

    // Initialize the DP table with -1
    vector<vector<double>> dp(1 << n, vector<double>(n, -1));

    // Calculate the total cost using the dynamic programming TSP algorithm
    double totalCost = tsp(1, 0, distances, dp);

    cout << "Total cost of the tour: " << totalCost << endl;

    return 0;
}
