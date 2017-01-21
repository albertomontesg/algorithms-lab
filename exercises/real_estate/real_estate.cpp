
#include <iostream>
#include <vector>
#include <algorithm>
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



void real_estate() {
    int N, M, S;
    cin >> N >> M >> S;

    const int MAX = 100;

    Graph G(N+M+S+2);
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
    EdgeWeightMap weightmap = get(edge_weight, G);
    ReverseEdgeMap revedgemap = get(edge_reverse, G);
    ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

    Vertex src = vertex(N+M+S, G);
    Vertex sink = vertex(N+M+S+1, G);

    // Store the graph
    for (int i = 0; i < N; i++) { eaG.addEdge(src, i, 1, 0); }
    for (int i = 0; i < S; i++) {
        long l; cin >> l;
        eaG.addEdge(N+M+i, sink, l, 0);
    }
    for (int i = 0; i < M; i++) {
        int s; cin >> s;
        eaG.addEdge(N+i, N+M+s-1, 1, 0);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            long b; cin >> b;
            eaG.addEdge(i, N+j, 1, MAX-b);
        }
    }

    successive_shortest_path_nonnegative_weights(G, src, sink);
    int cost = find_flow_cost(G);
    int flow = 0;
    // Iterate over all edges leaving the source to sum up the flow values.
    OutEdgeIt e, eend;
    for(tie(e, eend) = out_edges(vertex(src,G), G); e != eend; ++e) {
        flow += capacitymap[*e] - rescapacitymap[*e];
    }
    cost = flow*MAX - cost;

    cout << flow << " " << cost << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        real_estate();
    }
}
