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
    Graph G(2 * N);
	WeightMap weightmap = get(edge_weight, G);

    int pos_in, pos_out, v;
    Edge e; bool success;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j <= i; j++) {
            pos_in = i * (i + 1) / 2 + j;
			pos_out = pos_in + N;
            cin >> v;
            tie(e, success) = add_edge(pos_in, pos_out, G);
            weightmap[e] = v;
            if (j > 0) {
				int pos_left_in = pos_in - 1, pos_left_out = pos_out - 1;
                add_edge(pos_left_out, pos_in, G);
                add_edge(pos_out, pos_left_in, G);
            }
            if (i < k - 1) {
				int pos_down_left_in = pos_in + (i + 1);
				int pos_down_left_out = pos_down_left_in + N;
				int pos_down_right_in = pos_down_left_in + 1;
				int pos_down_right_out = pos_down_right_in + N;
                add_edge(pos_out, pos_down_left_in, G);
                add_edge(pos_down_left_out, pos_in, G);
                add_edge(pos_out, pos_down_right_in, G);
                add_edge(pos_down_right_out, pos_in, G);
            }
        }
    }

    vector<vector<int> > distmap(3, vector<int>(N*2));
    // Compute the distance map for the three point (0,0), (k,0), (k,k)
    dijkstra_shortest_paths(G, N,
        distance_map(make_iterator_property_map(distmap[0].begin(), get(vertex_index, G))));
    dijkstra_shortest_paths(G, 2*N - k,
        distance_map(make_iterator_property_map(distmap[1].begin(), get(vertex_index, G))));
    dijkstra_shortest_paths(G, 2*N - 1,
        distance_map(make_iterator_property_map(distmap[2].begin(), get(vertex_index, G))));

    int minimum_burden = INT_MAX;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j <= i; j++) {
            pos_in = i * (i + 1) / 2 + j;
            if (pos_in == 0 || pos_in == N - k || pos_in == N -1)
				continue;
            tie(e, success) = edge(pos_in, pos_in+N, G);
            minimum_burden = min(minimum_burden,
                distmap[0][pos_in] + distmap[1][pos_in] + distmap[2][pos_in] + weightmap[e]);
        }
    }

    cout << minimum_burden << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        bobs_burden();
    }
}
