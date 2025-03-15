#include "dijkstras.h"

int main() {
    Graph G;
    //cout << "1\n";
    file_to_graph("src/small.txt", G); // Load graph from file
    //cout << "2\n";

    int source = 0;
    vector<int> previous(G.numVertices, UNDEFINED);
    //cout << "3\n";
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    //cout << "meow\n";

    cout << "Shortest distances from node " << source << ":\n";
    for (size_t i = 0; i < distances.size(); i++) {
        cout << "To " << i << " -> " << distances[i] << "\n";
    }

    // Extract the shortest path to a specific destination
    int destination = 3;
    vector<int> path = extract_shortest_path(distances, previous, destination);

    if (path.empty()) {
    cout << "Error: Path is empty. Check if previous[] was initialized correctly.\n";
}

    cout << "Shortest path from " << source << " to " << destination << ": ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
    
    print_path(path, path.size());

    return 0;
}