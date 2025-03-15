#include "dijkstras.h"
#include <algorithm>


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    //cout << "d1\n";
    int numVertices = G.numVertices;
    previous.assign(numVertices, UNDEFINED);
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = UNDEFINED;
    //priority_queue<pair<int, int>> minHeap;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});
    //cout << "d2\n";

    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        // if (u < 0 || u >= numVertices) {
        //     cerr << "Error: u out of range: " << u << endl;
        //     return distances;
        // }

        if (visited[u]) continue;
        visited[u] = true;
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            // if (v < 0 || v >= numVertices) {
            //     cerr << "Error: v out of range: " << v << endl;
            //     return distances;
            // }

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    // cout << "Previous Array:\n";
    // for (int i = 0; i < numVertices; i++) {
    //     cout << "Previous[" << i << "] = " << previous[i] << endl;
    // }
    return distances;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "Empty Path." << endl;
        return; 
    }
    for (int i = 0; i < total; ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    int node = destination;
    if (previous[node] == UNDEFINED || distances[node] == INF) {
        cout << "No path to " << destination << endl;
        return path;
    }
    while (node != UNDEFINED && distances[node] != 0) {
        path.push_back(node);
        node = previous[node];
    }
    if (distances[node] == 0) {
        path.push_back(node);
    }
    reverse(path.begin(), path.end());
    return path;
}

