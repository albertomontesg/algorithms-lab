
// STL includes
#include <vector>
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

// Namespaces
using namespace std;
using namespace boost;

// Directed graph with integer weights on edges.
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::vertex_descriptor      Vertex;
typedef graph_traits<Graph>::edge_descriptor        Edge;
// Property map edge -> weight
typedef property_map<Graph, edge_weight_t>::type    WeightMap;


void odd_route() {
    int n, m; cin >> n >> m;
    int s, t; cin >> s >> t;

    Graph G(4*n);
    WeightMap weightmap = get(edge_weight, G);

    /*
    Split all vertices u, 0 <= u < V(G) into 4 parts
    4*u (even length , even weight)
    4*u+1 (even length, odd weight)
    4*u+2 (odd length, even weight)
    4*u+3 (odd length, odd weight)
    */

    Edge e;
    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        tie(e, tuples::ignore) = add_edge(4*u,     4*v + 2 + w%2, G); weightmap[e] = w;
        tie(e, tuples::ignore) = add_edge(4*u + 1, 4*v + 3 - w%2, G); weightmap[e] = w;
        tie(e, tuples::ignore) = add_edge(4*u + 2, 4*v + w%2,     G); weightmap[e] = w;
        tie(e, tuples::ignore) = add_edge(4*u + 3, 4*v + 1 - w%2, G); weightmap[e] = w;
    }

    vector<int> dist(4 * n), pred(4 * n);
    dijkstra_shortest_paths(G, 4*s,
                            predecessor_map(make_iterator_property_map(pred.begin(),
                            get(vertex_index, G)))
                              .distance_map(make_iterator_property_map(dist.begin(),
                                get(vertex_index, G))
                              )
                           );
    if (dist[4*t + 3] == INT_MAX)
      cout << "no" << endl;
    else
      cout << dist[4*t + 3] << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        odd_route();
    }
}
