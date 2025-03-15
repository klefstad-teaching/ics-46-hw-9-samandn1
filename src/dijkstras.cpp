#include "dijkstras.h"

//const int UNDEFINED = -1;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = UNDEFINED;
    //priority_queue<pair<int,int>> minHeap;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});

    while (!minHeap.empty()){
        // int u = minHeap.
        int u = minHeap.top().second;
        minHeap.pop();

        if (visited[u]) continue;
        visited[u] = true;
        for (const Edge& edge : G[u]){
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    stack<int> pathStack;
    vector<int> path;

    for (int at = destination; at != UNDEFINED; at = previous[at]) {
        pathStack.push(at);
    }

    while (!pathStack.empty()) {
        path.push_back(pathStack.top());
        pathStack.pop();
    }

    return path;
}

void print_path(const vector<int>& v, int total){
    for(int i=0; i < total; ++i)
        cout << v[i] << " ";
}


