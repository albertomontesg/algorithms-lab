
#include <iostream>
#include <vector>
#include <queue>
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


void satellites() {
    int g, s, l;
    cin >> g >> s >> l;

    Graph G(g+s+2);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
    ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

    Vertex src = vertex(g+s, G);
    Vertex sink = vertex(g+s+1, G);

    int from, to;
    for (int i = 0; i < l; i++) {
        cin >> from >> to;
        eaG.addEdge(from, g + to, 1);
    }
    for (int i = 0; i < g; i++) {
        eaG.addEdge(src, i, 1);
    }
    for (int i = g; i < g + s; i++) {
        eaG.addEdge(i, sink, 1);
    }

    push_relabel_max_flow(G, src, sink);

    // BFS to find vertex set S
	vector<int> vis(g+s+2, false); // visited flags
	std::queue<int> Q; // BFS queue (from std:: not boost::)
	vis[src] = true; // Mark the source as visited
	Q.push(src);
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

    int count_g = 0, count_s = 0;
    vector<int> result;
    for (int i = 0; i < g; i++) {
        if (!vis[i]) {
            count_g++;
            result.push_back(i);
        }
    }
    for (int i = g; i < g + s; i++) {
        if (vis[i]) {
            count_s++;
            result.push_back(i - g);
        }
    }

    cout << count_g << " " << count_s << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
        if (i == result.size() - 1) cout << endl;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        satellites();
    }
}
