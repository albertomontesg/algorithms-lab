
#include <iostream>
#include <map>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/connected_components.hpp>
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


void sweepers() {
    int n, m, s, p;
    cin >> n >> m >> s;

    Graph G(n+2);
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
    ReverseEdgeMap revedgemap = get(edge_reverse, G);
    EdgeAdder eaG(G, capacitymap, revedgemap);
    Vertex v_source = n, v_target = n + 1;

    vector<int> degree(n, 0);
    vector<bool> has_edges(n, false);
    has_edges[n] = true; has_edges[n+1];

    for (int i = 0; i < s; i++) {
        cin >> p;
        eaG.addEdge(v_source, p, 1);
        degree[p]++;
        has_edges[p] = true;
    }
    for (int i = 0; i < s; i++) {
        cin >> p;
        eaG.addEdge(p, v_target, 1);
        degree[p]++;
        has_edges[p] = true;
    }

    int x, y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        eaG.addEdge(x, y, 1);
        eaG.addEdge(y, x, 1);
        degree[x]++; degree[y]++;
        has_edges[x] = true; has_edges[y] = true;
    }

    int flow = push_relabel_max_flow(G, v_source, v_target);

    vector<Vertex> componentmap(n+2);
	connected_components(G, make_iterator_property_map(componentmap.begin(), get(vertex_index, G)));

    bool result = flow == s;        // First check if the flow is equal the number of sweepers
    // Now check the degree of all the nodes
    for (int i = 0; i < n; i++)
        if (degree[i] % 2 != 0) result = false;
    // Now check that all the nodes from the same component that source, are the ones that have the
    // edges -> the edges are reachable.
    int ref_component = componentmap[n];
    for (int i = 0; i < n; i++) {
        if (has_edges[i] && componentmap[i] != ref_component) result = false;
    }

    if (result) cout << "yes" << endl;
    else cout << "no" << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        sweepers();
    }
}
