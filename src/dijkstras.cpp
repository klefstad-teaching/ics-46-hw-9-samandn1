#include "dijkstras.h"
#include <algorithm>


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    //cout << "d1\n";
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    previous.assign(numVertices, -1);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = UNDEFINED;
    //priority_queue<pair<int, int>> minHeap;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap; //vertex, weight
    minHeap.push({source, 0});
    //cout << "d2\n";

    while (!minHeap.empty()) {
        int u = minHeap.top().first;
        minHeap.pop();

        

        if (visited[u]) continue;
        visited[u] = true;
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;


            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }

    return distances;
}

void print_path(const vector<int>& v, int total) {
    // if (v.empty()) {
    //     cout << "Empty Path." << endl;
    //     return; 
    // }
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;

}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) return path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

