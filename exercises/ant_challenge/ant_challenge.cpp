
// STL includes
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/graph_utility.hpp>

// Namespaces
using namespace std;
using namespace boost;

// Directed graph with integer weights on edges.
typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::vertex_descriptor      Vertex;
typedef graph_traits<Graph>::edge_descriptor        Edge;
typedef graph_traits<Graph>::edge_iterator          EdgeIt;
// Property map edge -> weight
typedef property_map<Graph, edge_weight_t>::type    WeightMap;


void graphs() {
    int n, e, s, a, b;
    cin >> n >> e >> s >> a >> b;

    vector<Graph> Gs(s);
    vector<WeightMap> weightmaps(s);
    for (int i = 0; i < s; i++) {
        weightmaps[i] = get(edge_weight, Gs[i]);
    }

    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;

        for (int j = 0; j < s; j++) {
            int w; cin >> w;
            Edge edge_to_add; bool success;
            tie(edge_to_add, success) = add_edge(u, v, Gs[j]);
            weightmaps[j][edge_to_add] = w;
        }
    }

    Graph G;
    WeightMap weightmap = get(edge_weight, G);

    // For every specie compute the Prim shortest path and then add the edges into a global graph
    for (int i = 0; i < s; i++) {
        int v; cin >> v;
        vector<Vertex> primpredmap(n);
        prim_minimum_spanning_tree(Gs[i], make_iterator_property_map(primpredmap.begin(), get(vertex_index, Gs[i])));

        Edge edge_s; bool success;
        Edge new_edge; bool new_success;
        for (int j = 0; j < n; j++) {
            if (j == primpredmap[j]) { continue; }

            Vertex source = j, target = primpredmap[j];
            tie(edge_s, success) = edge(source, target, Gs[i]);
            int weight = weightmaps[i][edge_s];
            tie(new_edge, new_success) = add_edge(j, primpredmap[j], G);
            weightmap[new_edge] = weight;

        }
    }

    // Compute the dijkstra shortest path over the global graph
    vector<int> distmap(n);
    vector<Vertex> predmap(n);
    Vertex start = a;
    Vertex end = b;
    dijkstra_shortest_paths(G, start,
        predecessor_map(make_iterator_property_map(
            predmap.begin(), get(vertex_index, G)
        )).
        distance_map(make_iterator_property_map(
            distmap.begin(), get(vertex_index, G)
        ))
    );

    cout << distmap[end] << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        graphs();
    }
}
