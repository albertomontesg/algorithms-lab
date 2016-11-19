
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
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
typedef	graph_traits<Graph>::out_edge_iterator			OutEdgeIt;

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



void algocoon() {
    int n, m; cin >> n >> m;

    Graph G(n);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

    for (int i = 0; i < m; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        eaG.addEdge(from, to, cost);
    }

    int best_src = -1, best_sink = -1, best_value = numeric_limits<int>::max();
    int flow;
    for (int i = 1; i < n; i++) {
        flow = push_relabel_max_flow(G, 0, i);
        if (flow < best_value) {
            best_value = flow; best_src = 0; best_sink = i;
        }
        flow = push_relabel_max_flow(G, i, 0);
        if (flow < best_value) {
            best_value = flow; best_src = i; best_sink = 0;
        }
    }


    flow = push_relabel_max_flow(G, best_src, best_sink);

    // BFS to find vertex set S
	vector<bool> vis(n, false); // visited flags
	std::queue<int> Q; // BFS queue (from std:: not boost::)
	vis[best_src] = true; // Mark the source as visited
	Q.push(best_src);
	while (!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		OutEdgeIt ebeg, eend;
		for (tie(ebeg, eend) = out_edges(u, G); ebeg != eend; ++ebeg) {
			const int v = target(*ebeg, G);
			// Only follow edges with spare capacity
			if (rescapacitymap[*ebeg] == 0 || vis[v]) continue;
			vis[v] = true;
			Q.push(v);
		}
	}

	cout << flow << endl;
    cout << count(vis.begin(), vis.end(), true);
    for (int i = 0; i < n; ++i) {
		if (vis[i]) cout << " " << i;
	}
	cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        algocoon();
    }
}
