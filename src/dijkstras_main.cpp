#include "dijkstras.h"

string get_arg(int argc, char *argv[], string def) {
    if (argc > 1) return argv[1];
    return def; 
}

int main(int argc, char *argv[]) {
    string filename = get_arg(argc, argv, "src/small.txt");
    Graph G;
    file_to_graph(filename, G);
    int source = 0;
    int numOfVertices = G.size();
    vector<int> previous(numOfVertices, -1);
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    for (int i = 0; i < numOfVertices; ++i) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }
    return 0;
}
