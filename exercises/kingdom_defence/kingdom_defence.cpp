
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
typedef	adjacency_list_traits<vecS, vecS, directedS> 				Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
// Interior Property Maps
typedef	property_map<Graph, edge_capacity_t>::type					EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type			ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type					ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor						Vertex;
typedef	graph_traits<Graph>::edge_descriptor						Edge;
typedef graph_traits<Graph>::edge_iterator              			EdgeIt;


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


void kingdom_defence() {
    int l, p;
    cin >> l >> p;

    Graph G(l+2);
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

    Vertex src = vertex(l, G);
    Vertex sink = vertex(l+1, G);

    long total_defenders = 0;
    long total_available = 0;
    for (int i = 0; i < l; i++) {
        long g, d;
        cin >> g >> d;
        Vertex location = vertex(i, G);
        eaG.addEdge(src, location, g);
        eaG.addEdge(location, sink, d);
        total_defenders += d;
        total_available += g;
    }

    for (int i = 0; i < p; i++) {
        int f, t;
        long c, C;
        cin >> f >> t >> c >> C;
        eaG.addEdge(f, t, C - c);
        if (c > 0) {
            eaG.addEdge(f, sink, c);
            total_defenders += c;
            eaG.addEdge(src, t, c);
            total_available += c;
        }
    }

    long flow = push_relabel_max_flow(G, src, sink);

    bool result = flow == total_defenders;

    if (result) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        kingdom_defence();
    }
}
