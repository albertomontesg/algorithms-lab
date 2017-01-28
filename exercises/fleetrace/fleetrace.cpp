#include <vector>
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
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


void fleetrace() {
  int B, S, P;
  cin >> B >> S >> P;

  const int MAX_COST = 50;

  // Create Graph and Maps
  Graph G(B+2*S+2);
  EdgeCapacityMap capacitymap = get(edge_capacity, G);
  EdgeWeightMap weightmap = get(edge_weight, G);
  ReverseEdgeMap revedgemap = get(edge_reverse, G);
  ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
  EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

  Vertex src_vertex = B+2*S, target_vertex = B+2*S+1;

  for (int i = 0; i < B; i++) eaG.addEdge(src_vertex, i, 1, 0);
  for (int i = 0; i < 2*S; i++) eaG.addEdge(B+i, target_vertex, 1, 0);
  for (int b = 0; b < B; b++) {
    for (int s = 0; s< S; s++) {
      eaG.addEdge(b, B+s, 1, MAX_COST);
    }
  }

  for (int i = 0; i < P; i++) {
    int b, s, c; cin >> b >> s >> c;
    eaG.addEdge(b, B+s, 1, MAX_COST - c);
  }

  successive_shortest_path_nonnegative_weights(G, src_vertex, target_vertex);
  int cost = find_flow_cost(G), flow = 0;
  OutEdgeIt e, eend;
  for(tie(e, eend) = out_edges(vertex(src_vertex,G), G); e != eend; ++e) {
      flow += capacitymap[*e] - rescapacitymap[*e];
  }
  cout << MAX_COST * flow - cost << endl;

}

int main() {
  ios_base::sync_with_stdio(false);
  int T; cin >> T;
  for (int i = 0; i < T; i++) fleetrace();
}
