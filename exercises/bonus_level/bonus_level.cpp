// Includes
// ========
// STL includes
#include <iostream>
#include <cstdlib>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
// Namespaces
using namespace boost;
using namespace std;

// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor,
                property <edge_weight_t, long> > > > > Graph;
// Interior Property Maps
typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t >::type       EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    EdgeWeightMap &weightmap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap)
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

    void addEdge(int u, int v, long c, long w) {
        Edge e, reverseE;
        tie(e, tuples::ignore) = add_edge(u, v, G);
        tie(reverseE, tuples::ignore) = add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w;
        capacitymap[reverseE] = 0;
        weightmap[reverseE] = -w;
        revedgemap[e] = reverseE;
        revedgemap[reverseE] = e;
    }
};

void bonus_level() {
    int n; cin >> n;

	const int MAX_COST = 100;
	// Create Graph and Maps
    Graph G(3 * n * n);
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
    EdgeWeightMap weightmap = get(edge_weight, G);
    ReverseEdgeMap revedgemap = get(edge_reverse, G);
    EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

	Vertex src = add_vertex(G);
	Vertex sink = add_vertex(G);

	int a, pos;
    for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a;
			pos = 3 * j + 3 * n * i;
			eaG.addEdge(pos, pos + 1, 1, MAX_COST - a);
			eaG.addEdge(pos, pos + 2, 1, MAX_COST);
			if (i != n - 1) {
				eaG.addEdge(pos + 1, pos + 3 * n, 1, 0);
				eaG.addEdge(pos + 2, pos + 3 * n, 1, 0);
			}
			if (j != n -1) {
				eaG.addEdge(pos + 1, pos + 3, 1, 0);
				eaG.addEdge(pos + 2, pos + 3, 1, 0);
			}
		}
	}
	eaG.addEdge(src, 0, 2, 0);
	eaG.addEdge(3 * n * n - 1, sink, 1, 0);
	eaG.addEdge(3 * n * n - 2, sink, 1, 0);

	successive_shortest_path_nonnegative_weights(G, src, sink);
    int cost = find_flow_cost(G);
	cout << - cost + 2 * (2 * n - 1) * MAX_COST << endl;

}

int main() {
    int T; cin >> T;
    for (int t = 0; t < T; t++){
        bonus_level();
    }
}
