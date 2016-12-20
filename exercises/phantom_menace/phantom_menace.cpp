/******
Given a directed graph find how many vertex need to be removed to disconect one set of vertex with
another set.
This is solve creating a graph with an income and outcome node for each vertex. All the edges must
have capacity one and then finding the mincut of the graph is possible to find the number of vertex
required to disconnect the two sets of vertex. The mincut is found computing the maximum flow.
******/

// Includes
// ========
// STL includes
#include <iostream>
#include <cstdlib>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
// Namespaces
using namespace boost;
using namespace std;

// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
// Interior Property Maps
typedef	property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::edge_descriptor			Edge;
typedef	graph_traits<Graph>::out_edge_iterator			OutEdgeIt;

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
	Graph &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:
	// to initialize the Object
	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

	// to use the Function (add an edge)
	void addEdge(int from, int to, long capacity) {
		Edge e, reverseE;
		bool success;
		tie(e, success) = add_edge(from, to, G);
		tie(reverseE, success) = add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[reverseE] = 0;
		revedgemap[e] = reverseE;
		revedgemap[reverseE] = e;
	}
};


void phantom_menace() {
    int n, m, s, d;
    cin >> n >> m >> s >> d;

    // Create Graph and Maps
    Graph G(2*n+2);     // Input nodes: [0, n)  Output nodes: [n, 2*n)
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

    Vertex src = 2 * n, sink = 2 * n + 1;

    // Reading graphs edges
    int i, j;
    for (int k = 0; k < m; k++) {
        cin >> i >> j;
        eaG.addEdge(n + i, j, 1);
    }
    for (int k = 0; k < n; k++) eaG.addEdge(k, n + k, 1);
    // Read starting vertex
    for (int k = 0; k < s; k++) {
        cin >> i;
        eaG.addEdge(src, i, 1);
    }
    // Read ending vertex
    for (int k = 0; k < d; k++) {
        cin >> j;
        eaG.addEdge(n + j, sink, 1);
    }
    // Compute the min cut as max flow
    int flow = push_relabel_max_flow(G, src, sink);
    cout << flow << endl;

}


int main() {
    int T; cin >> T;
    for (int i = 0; i < T; i++) {
        phantom_menace();
    }
}
