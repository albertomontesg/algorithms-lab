#include <iostream>
#include <vector>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
// Namespaces
using namespace std;
using namespace boost;

// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef adjacency_list<vecS, vecS, undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		no_property,				// interior properties of vertices
		property<edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).
typedef graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef property_map<Graph, edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t


void return_of_the_jedi() {
    int N, I; cin >> N >> I;

    Graph G(N);	// creates an empty graph on n vertices
	WeightMap weightmap = get(edge_weight, G);

    Edge e; bool success;
    for (int j = 1; j < N; j++) {
        for (int k = 1; k <= N - j; k++) {
            int cost; cin >> cost;
            tie(e, success) = add_edge(j-1, j+k-1, G);
            weightmap[e] = cost;
        }
    }

    vector<Vertex> primpredmap(N);	// We MUST use this vector as an Exterior Property Map: Vertex -> Prim Predecessor
    prim_minimum_spanning_tree(G, make_iterator_property_map(primpredmap.begin(), get(vertex_index, G)));	// Prim from *vertices(G).first (usually 0)

    int totalweight = 0;
	for (int i = 0; i < N; ++i) {
		if (primpredmap[i] != i) {
			Edge e; bool success;
			tie(e, success) = edge(i, primpredmap[i], G);
			totalweight += weightmap[e];
		}
	}
    cout << totalweight << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int i = 0; i < T; i++) return_of_the_jedi();
}
