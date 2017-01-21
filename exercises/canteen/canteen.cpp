
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
// Namespaces
using namespace std;
using namespace boost;


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
typedef graph_traits<Graph>::out_edge_iterator          OutEdgeIt; // Iterator


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



void canteen() {
    int n; cin >> n;

    const int MAX_PRICE = 20;

    vector<int> a(n), c(n), s(n), p(n), v(n-1), e(n-1);
    for (int i = 0; i < n; i++) { cin >> a[i] >> c[i]; }
    for (int i = 0; i < n; i++) { cin >> s[i] >> p[i]; }
    for (int i = 0; i < n-1; i++) { cin >> v[i] >> e[i]; }

    // Create Graph and Maps
    Graph G(n+2);
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
    EdgeWeightMap weightmap = get(edge_weight, G);
    ReverseEdgeMap revedgemap = get(edge_reverse, G);
    ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

    Vertex src = n, sink = n+1;
    for (int i = 0; i < n; i++) {
        eaG.addEdge(src, i, a[i], c[i]);
        eaG.addEdge(i, sink, s[i], MAX_PRICE-p[i]);
        if (i < n-1) { eaG.addEdge(i, i+1, v[i], e[i]); }
    }

    // Compute flow and cost
    successive_shortest_path_nonnegative_weights(G, src, sink);
    int cost = find_flow_cost(G);
    int flow = 0;

    for (int i = 0; i < n; i++) {
        Edge ee; bool success;
        tie(ee, success) = edge(i, sink, G);
        int f = capacitymap[ee] - rescapacitymap[ee];
        flow += f;
        cost -= f * MAX_PRICE;
    }
    cost = -cost;

    int total_s = accumulate(s.begin(), s.end(), 0);
    string text = (total_s == flow) ? "possible " : "impossible ";
    cout << text << flow << " " << cost << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        canteen();
    }
}
