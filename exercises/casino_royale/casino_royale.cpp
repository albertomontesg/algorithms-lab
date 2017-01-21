
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
    ReverseEdgeMap &revedgemap;

public:
    EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap)
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

    Edge addEdge(int u, int v, long c, long w) {
        Edge e, reverseE;
        tie(e, tuples::ignore) = add_edge(u, v, G);
        tie(reverseE, tuples::ignore) = add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w;
        capacitymap[reverseE] = 0;
        weightmap[reverseE] = -w;
        revedgemap[e] = reverseE;
        revedgemap[reverseE] = e;
        return e;
    }
};

void casino_royale() {
    int n, m, l;
    cin >> n >> m >> l;

    const int MAX_PRIORITY = 1<<7;

    // Create Graph and Maps
    Graph G(n+2);
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
    EdgeWeightMap weightmap = get(edge_weight, G);
    ReverseEdgeMap revedgemap = get(edge_reverse, G);
    ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);
    Vertex v_source = n, v_target = n + 1;

    for (int i = 0; i < n-1; i++) { eaG.addEdge(i, i+1, l, MAX_PRIORITY); }
    eaG.addEdge(v_source, 0, l, 0);
    eaG.addEdge(n-1, v_target, l, 0);

    // Add the missions edges
    int x, y, q;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> q;
        eaG.addEdge(x, y, 1, (MAX_PRIORITY*(y-x) - q));
    }

    // Find MaxFlowMinCost
    successive_shortest_path_nonnegative_weights(G, v_source, v_target);
    int cost = find_flow_cost(G), flow = 0;
    OutEdgeIt e, eend;
    for(tie(e, eend) = out_edges(vertex(v_source,G), G); e != eend; ++e) {
        flow += capacitymap[*e] - rescapacitymap[*e];
    }
    cost -= MAX_PRIORITY * (n-1) * flow;
    cout << -cost << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        casino_royale();
    }
}
