
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

    // For each specia graph search the minimum spanning tree to know which is the
    // graph each specie see and can travel
    vector<vector<Vertex> > primpredmap(s, vector<Vertex>(n));
    for (int i = 0; i < s; i++) {
        Vertex v; cin >> v;
        prim_minimum_spanning_tree(Gs[i], make_iterator_property_map(primpredmap[i].begin(), get(vertex_index, Gs[i])), root_vertex(v));
    }

    // Merge all spanning trees choosing for each edge the one with minimum weight
    Graph G;
    WeightMap weightmap = get(edge_weight, G);

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < n; j++) {
            Vertex source = j;
            Vertex target = primpredmap[i][j];
            Edge edge_to_look, edge_specie;
            bool found, success_specie;
            tie(edge_to_look, found) = edge(j, primpredmap[i][j], G);
            // tie(edge_specie, success_specie) = edge(j, primpredmap[i][j], Gs[i]);
            if (found) {
                // The edge already exist so it is only necessary to update to the minimum weight
                // weightmap[edge_to_look] = min(weightmap[edge_to_look], weightmaps[i][edge_specie]);
            } else {
                Edge new_edge; bool new_success;
                tie(new_edge, new_success) = add_edge(source, target, G);
                // weightmap[new_edge] = weightmaps[i][edge_specie];
            }
        }
    }
    //
    //
    // // Compute the dijkstra shortest path
    // vector<int> distmap(n);
    // vector<Vertex> predmap(n);
    // Vertex start = a;
    // Vertex end = b;
    // dijkstra_shortest_paths(G, start,
    //     predecessor_map(make_iterator_property_map(
    //         predmap.begin(), get(vertex_index, G)
    //     )).
    //     distance_map(make_iterator_property_map(
    //         distmap.begin(), get(vertex_index, G)
    //     ))
    // );
    //
    // cout << distmap[end] << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        graphs();
    }
}
