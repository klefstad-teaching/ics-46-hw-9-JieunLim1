#include "dijkstras.h"
#include <iostream>

using namespace std;

int main() {
    Graph G;
    int source =  ; // Define source vertex

    try {
        file_to_graph("../src/word.txt", G); // Load graph from file
    } catch (const std::runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    for (int i = 0; i < G.numVertices; i++) {
        if (i == source) continue;
        vector<int> path = extract_shortest_path(distances, previous, i);
        cout << "Shortest path from " << source << " to " << i << ": ";
        print_path(path, distances[i]);
    }

    return 0;
}
