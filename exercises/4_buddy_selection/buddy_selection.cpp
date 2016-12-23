
// STL includes
#include <vector>
#include <string>
#include <iostream>
#include <map>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

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


void buddy_selection() {
    int n, c, f;
    cin >> n >> c >> f;

    Graph G_s(n);
    WeightMap weightmap_s = get(edge_weight, G_s);

    /* Create the graph with all the edges that have higher weight than f and perform maximum
    cardinality matching to find a more optimal solution of the problem. If cardinality matching is
    equal to n/2 it means that the solution propoesed `f` is not the optimal */
    map<string, vector<int> > characteristics;
    string name;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < c; j++) {
            cin >> name;
            characteristics[name].push_back(i);
        }
    }

    // Iterate over all characteristics and create vertex with weight
    for (auto it = characteristics.begin(); it != characteristics.end(); it++) {
        vector<int> people = it->second;
        int np = people.size(); // Number of people that share the same caracteristic
        if (np <= 1) continue;

        // Lets iterate over all people that share the same characteristic
        for (int i = 0; i < np; i++) {
            for (int j = i+1; j < np; j++) {
                int p_i = people[i], p_j = people[j];
                Edge connection; bool success;
                tie(connection, success) = edge(p_i, p_j, G_s);
                if (success) { // The connection already exists
                    weightmap_s[connection]++;
                } else {
                    tie(connection, success) = add_edge(p_i, p_j, G_s);
                    weightmap_s[connection] = 1;
                }
            }
        }
    }

    // Create final graph
    Graph G(n);
    WeightMap weightmap = get(edge_weight, G);

    // Now iterate over all edges and substract the edges with a weight less than `f`
    EdgeIt eib, eie;
    for (tie(eib, eie) = edges(G_s); eib != eie; eib++) {
        Edge edge_c = *eib;
        int weight = weightmap_s[edge_c];
        if (weight > f) {
            Edge edg; bool success;
            tie(edg, success) = add_edge(source(edge_c, G), target(edge_c, G), G);
            weightmap[edg] = weight - f;
        }
    }

    // Compute Matching
    vector<Vertex> matemap(n); // Use as an Exterior Property Map: Vertex -> Matc
    edmonds_maximum_cardinality_matching (
        G,
        make_iterator_property_map(matemap.begin(), get(vertex_index , G))
    );
    // Look at the matching size
    int matchingsize = matching_size (
        G,
        make_iterator_property_map (matemap.begin(), get(vertex_index , G))
    );

    if (matchingsize == n/2) {
        cout << "not optimal" << endl;
    } else {
        cout << "optimal" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        buddy_selection();
    }
}
