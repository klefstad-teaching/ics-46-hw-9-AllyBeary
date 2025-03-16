#include "dijkstras.h"
#include <algorithm>
#include <iostream>
using namespace std;

pair<int, int> extractVertexWithMinWeight(priority_queue<pair<int, int>>& minHeap) {
    pair<int, int> topElement = minHeap.top(); 
    minHeap.pop();
    return {topElement.second, topElement.first};
}

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) { // computes the shortest paths for each of the vertices from the start vertex
    int numOfVertices = G.size();
    vector<int> distances(numOfVertices, INF);
    vector<bool> visited(numOfVertices, false);
    distances[source] = 0; // start vertex source has a distance of 0 from itself
    previous[source] = -1; // start vertex source does not have a previous vertex (predecessor) so -1 
    priority_queue<pair<int, int>> minHeap; // pair<vertex, weight>
    minHeap.push({0, source}); 
    while (!minHeap.empty()) {
        auto [minWeight, u] = extractVertexWithMinWeight(minHeap); // get the vertex u with the smallest distance from 
        if (visited[u]) continue;
        visited[u] = true;
        for (const Edge& e : G[u]) {
            int v = e.dst; // current vertex u's adjacent vertex v
            int weight = e.weight;
            int altDst = distances[u] + weight; // alternative distance is current vertex u's distance plus the weight of the connecting edge to adjacent vertex v 
            if (!visited[v] && altDst < distances[v]) { // if alternative distance is shorter than the adjacent vertex v's current distance
                distances[v] = altDst; // update adjacent vertex v's distance to alternative distance
                previous[v] = u; // update adjacent vertex v's predecessor to be current vertex u
                minHeap.push({distances[v], v}); // push the updated distance for adjacent vertex v to the minority heap
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> v;
    if (distances[destination] == INF) return v;
    for (int dest = destination; dest != -1; dest = previous[dest]) 
        v.push_back(dest);
    reverse(v.begin(), v.end());
    return v;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "No path found" << endl;
        return;
    }
    for (const int& vertex : v) {
        cout << vertex << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}
