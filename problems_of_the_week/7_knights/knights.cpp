
#include <iostream>
#include <map>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
// Namespaces
using namespace std;
using namespace boost;


// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
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
typedef graph_traits<Graph>::edge_iterator              EdgeIt;


// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder {
	Graph &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:
	// to initialize the Object
	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

	// to use the Function (add an edge)
	Edge addEdge(int from, int to, long capacity) {
		Edge e, reverseE;
		bool success;
		tie(e, success) = add_edge(from, to, G);
		tie(reverseE, success) = add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[reverseE] = 0;
		revedgemap[e] = reverseE;
		revedgemap[reverseE] = e;
        return e;
	}
};


void knights() {
    int m, n, k, c;
    cin >> m >> n >> k >> c;

    Graph G(2*m*n+2);
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

    // Create graph representing the cave
    Vertex src = vertex(2*n*m, G);
    Vertex sink = vertex(2*n*m+1, G);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int pos_out = i*m + j;
            int pos_in = pos_out + n*m;
            int pos_out_right = pos_out + 1;
            int pos_in_right = pos_out_right + n*m;
            int pos_out_down = pos_out + m;
            int pos_in_down = pos_out_down + n*m;
            // Conect inner node with outer node
            eaG.addEdge(pos_in, pos_out, c);
            if (j < m-1) {
                // Connecting node with the one on the right
                eaG.addEdge(pos_out, pos_in_right, 1);
                eaG.addEdge(pos_out_right, pos_in, 1);
            }
            if (i < n-1) {
                // Connecting node with the one on the bottom
                eaG.addEdge(pos_out, pos_in_down, 1);
                eaG.addEdge(pos_out_down, pos_in, 1);
            }
            if (i == 0 || i == n-1) {
                // Connecting top and bottom nodes to sink
                eaG.addEdge(pos_out, sink, 1);
            }
            if (j == 0 || j == m-1) {
                // Connecting left and right nodes to sink
                eaG.addEdge(pos_out, sink, 1);
            }
        }
    }

    // Add edge from the source to the intersection representing the starting point of the knight
    for (int i = 0; i < k; i++) {
        int x, y; cin >> x >> y;
        int pos = y*m+x + n*m;
        eaG.addEdge(src, pos, 1);
    }

    // Compute the maximum number of knights as maximum flow
    long flow = push_relabel_max_flow(G, src, sink);
    cout << flow << endl;

}

int main() {
    int T; cin >> T;
    for (int t=0; t < T; t++){
        knights();
    }
}
