#include <vector>
#include "dijkstras.h"
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    vector<bool> visited(n, false);
    previous.assign(n, -1);

    distances[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source}); // First element is weight, second is vertex

    while (!minHeap.empty()) {
        int current_weight = minHeap.top().first;
        int current_vertex = minHeap.top().second;
        minHeap.pop();

        if (visited[current_vertex]) continue;
        visited[current_vertex] = true;

        for (Edge e : G[current_vertex]) { // vector of vector of edges
            int nextV = e.dst;
            int nextW = e.weight;

            if (!visited[nextV] && distances[current_vertex] + nextW < distances[nextV]) {
                distances[nextV] = distances[current_vertex] + nextW;
                previous[nextV] = current_vertex;
                minHeap.push({distances[nextV], nextV});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int i = destination; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.size() == 1 && total == INF) {
        cout << "No path exists." << endl;
        return;
    }
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}
