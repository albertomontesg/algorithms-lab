
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
#include <boost/graph/graph_utility.hpp>

// Namespaces
using namespace std;
using namespace boost;

// Directed graph with integer weights on edges.
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::vertex_descriptor      Vertex;
typedef graph_traits<Graph>::edge_descriptor        Edge;
typedef graph_traits<Graph>::edge_iterator          EdgeIt;
// Property map edge -> weight
typedef property_map<Graph, edge_weight_t>::type    WeightMap;



void odd_route() {
    int n, m; cin >> n >> m;
    int s, t; cin >> s >> t;

    Graph G(n);
    WeightMap weightmap = get(edge_weight, G);

    Edge edge; bool success;
    int s_i, t_i, w_i;
    for (int i = 0; i < m; i++) {
        cin >> s_i >> t_i >> w_i;
        tie(edge, success) = add_edge(s_i, t_i, G);
        weightmap[edge] = w_i;
    }

    // Dynamic Programming
    

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        odd_route();
    }
}
