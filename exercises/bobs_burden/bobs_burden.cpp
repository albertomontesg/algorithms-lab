// Includes
// ========
// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
// Namespaces
using namespace std;
using namespace boost;

// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef adjacency_list<vecS, vecS, directedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		no_property,				// interior properties of vertices
		property<edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).
typedef graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef property_map<Graph, edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t


void bobs_burden() {
    int k; cin >> k;

    int N = k * (k+1) / 2;
    Graph G(k*(k+1));
	WeightMap weightmap = get(edge_weight, G);

    int pos, v;
    Edge e; bool success;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j <= i; j++) {
            pos = i * (i + 1) / 2 + j;
            cin >> v;
            tie(e, success) = add_edge(N + pos, pos, G);
            weightmap[e] = v;
            if (j > 0 && i > 0) {
                tie(e, success) = add_edge(pos, N + pos - 1, G);
                weightmap[e] = 0;
                tie(e, success) = add_edge(pos - 1, N + pos, G);
                weightmap[e] = 0;
            }
            if (i < k - 1) {
                tie(e, success) = add_edge(pos, N + pos + i + 1, G);
                weightmap[e] = 0;
                tie(e, success) = add_edge(pos + i + 1, N + pos, G);
                weightmap[e] = 0;
                tie(e, success) = add_edge(pos, N + pos + i + 2, G);
                weightmap[e] = 0;
                tie(e, success) = add_edge(pos + i + 2, N + pos, G);
                weightmap[e] = 0;
            }
        }
    }

    vector<vector<int> > distmap(3, vector<int>(N*2));
    // Compute the distance map for the three point (0,0), (k,0), (k,k)
    dijkstra_shortest_paths(G, 0,
        predecessor_map(make_iterator_property_map(distmap[0].begin(), get(vertex_index, G))));
    dijkstra_shortest_paths(G, (k - 1) * (k - 2) / 2,
        predecessor_map(make_iterator_property_map(distmap[1].begin(), get(vertex_index, G))));
    dijkstra_shortest_paths(G, N - 1,
        predecessor_map(make_iterator_property_map(distmap[2].begin(), get(vertex_index, G))));

    int minimum_burden = INT_MAX;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j <= i; j++) {
            pos = i * (i + 1) / 2 + j;
            if (pos == 0 || pos == (k - 1) * (k - 2) / 2 || pos == N -1) continue;
            tie(e, success) = edge(N+pos, pos, G);
            minimum_burden = min(minimum_burden,
                distmap[0][N+pos] + distmap[1][N+pos] + distmap[2][N+pos] + weightmap[e]);
        }
    }

    cout << minimum_burden << endl;

    // vector<Vertex> predmap(V);	// We will use this vector as an Exterior Property Map: Vertex -> Dijkstra Predecessor
	// vector<int> distmap(V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	// Vertex start = 0;
	// dijkstra_shortest_paths(G, start, // We MUST provide at least one of the two maps
	// 	predecessor_map(make_iterator_property_map(predmap.begin(), get(vertex_index, G))).	// predecessor map as Named Parameter
	// 	distance_map(make_iterator_property_map(distmap.begin(), get(vertex_index, G))));	// distance map as Named Parameter


}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        bobs_burden();
    }
}
