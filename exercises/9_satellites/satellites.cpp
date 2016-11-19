
#include <iostream>
#include <vector>
#include <algorithm>
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



void satellites() {
    int g, s, l;
    cin >> g >> s >> l;

    vector<int> ground(l), sat(l), max_ground(g, 0), max_sat(s, 0);
    int max_cap = 0;
    for (int i = 0; i < l; i++) {
        int from, to;
        cin >> from >> to;
        ground[i] = from; sat[i] = to;
        max_ground[from]++; max_sat[to]++;
        max_cap = max(max_cap, max_ground[from]);
        max_cap = max(max_cap, max_sat[to]);
    }

    Graph G(g+s+2);
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
    EdgeWeightMap weightmap = get(edge_weight, G);
    ReverseEdgeMap revedgemap = get(edge_reverse, G);
    ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

    Vertex src = vertex(g+s, G);
    Vertex sink = vertex(g+s+1, G);

    // for (int i = 0; i < g; i++) {
    //     eaG.addEdge(i, sink, max_ground[i], 1);
    // }
    // for (int i = 0; i < s; i++) {
    //     eaG.addEdge(g+l+i, sink, max_sat[i], 1);
    // }
    // for (int i = 0; i < l; i++) {
    //     eaG.addEdge(src, g+i, 1, 0);
    //     eaG.addEdge(g+i, ground[i], 1, 0);
    //     eaG.addEdge(g+i, g+l+sat[i], 1, 0);
    // }




    // Build edge connections of the graph
    for (int i = 0; i < g; i++) {
        eaG.addEdge(src, i, max_ground[i], 0);
        eaG.addEdge(i, sink, max_ground[i], 1+max_cap-max_ground[i]);
    }
    for (int i = 0; i < s; i++) {
        eaG.addEdge(g+i, sink, max_sat[i], 1+max_cap-max_sat[i]);
    }
    for (int i = 0; i < l; i++) {
        eaG.addEdge(ground[i], g+sat[i], 1, 0);
    }

    successive_shortest_path_nonnegative_weights(G, src, sink);
    int cost = find_flow_cost(G);
    int flow = 0;
    // Iterate over all edges leaving the source to sum up the flow values.
    OutEdgeIt e, eend;
    for(tie(e, eend) = out_edges(vertex(src,G), G); e != eend; ++e) {
        flow += capacitymap[*e] - rescapacitymap[*e];
    }
    assert(flow == l);

    cout << flow << " " << cost << endl << endl;;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        satellites();
    }
}
