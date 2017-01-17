
// STL includes
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

// Namespaces
using namespace std;
using namespace boost;

// Directed graph with integer weights on edges.
typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::vertex_descriptor  Vertex;
typedef graph_traits<Graph>::edge_descriptor    Edge;
typedef graph_traits<Graph>::edge_iterator      EdgeIt;
// Property map edge -> weight
typedef property_map<Graph, edge_weight_t>::type    WeightMap;


void graphs() {
    int n, m;
    cin >> n >> m;

    // Initialize graph and weightmap
    Graph G(n);
    WeightMap weightmap = get(edge_weight, G);

    // Store the graph
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        Edge e; bool success;
        tie(e, success) = add_edge(v, u, G);
        weightmap[e] = w;
    }

    // Find the Minimum Spanning Tree with Prim algorithm
    vector<int> predmap(n);
    Vertex start = 0;
    prim_minimum_spanning_tree(G, make_iterator_property_map(
        predmap.begin(), get(vertex_index, G)
    ), root_vertex(start));
    int w = 0;
    for (int j = 0; j < n; j++) {
        Edge e; bool success;
        tie(e, success) = edge(j, predmap[j], G);
        if ( success ) {
            w += weightmap[e];
        }
    }

    // Compute shortest t-u path in G
    vector<int> distmap(n);
    vector<Vertex> predmap_d(n);
    dijkstra_shortest_paths(G, start,
        predecessor_map(make_iterator_property_map(
            predmap_d.begin(), get(vertex_index, G)
        )).
        distance_map(make_iterator_property_map(
            distmap.begin(), get(vertex_index, G)
        ))
    );

    // Find the furthest vertex
    int max_distance = 0;
    for (int j = 1; j < n; j++) {
        if (distmap[j] < INT_MAX) {
            max_distance = max(max_distance, distmap[j]);
        }
    }

    cout << w << " " << max_distance << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        graphs();
    }
}
