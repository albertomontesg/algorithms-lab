
// STL includes
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

// Namespaces
using namespace std;
using namespace boost;

// Directed graph with integer weights on edges.
typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> >   DiGraph;
typedef graph_traits<DiGraph>::vertex_descriptor      Vertex;
typedef graph_traits<DiGraph>::edge_descriptor        Edge;
typedef graph_traits<DiGraph>::edge_iterator          EdgeIt;
// Property map edge -> weight
typedef property_map<DiGraph, edge_weight_t>::type    WeightMap;


void oh_her_majestys_secret_service() {
    int n, m, a, s, c, d;
    cin >> n >> m >> a >> s >> c >> d;

    DiGraph G(n);
    WeightMap weightmap = get(edge_weight, G);

    char w; int x, y, z;
    Edge edg; bool success;
    for (int i = 0; i < m; i++) {
        cin >> w >> x >> y >> z;

        tie(edg, success) = add_edge(x, y, G);
        weightmap[edg] = z;
        if (w == 'L') {
            tie(edg, success) = add_edge(y, x, G);
            weightmap[edg] = z;
        }
    }

    vector<int> agents(a), shelters(s);
    for (int i = 0; i < a; i++) cin >> agents[i];
    for (int i = 0; i < s; i++) cin >> shelters[i];

    // Compute one distance map per agent
    vector<vector<int> > distmap(a, vector<int>(n));
    for (int i = 0; i < a; i++) {
        dijkstra_shortest_paths(G, agents[i],
            distance_map(make_iterator_property_map(distmap[i].begin(), get(vertex_index, G))));
    }
    // Represent G' as the pairwise distance matrix T from agents to shelters.
    vector<vector<int> > T(a, vector<int>(s, INT_MAX));
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < s; j++) {
            T[i][j] = distmap[i][shelters[j]];
        }
    }

    // Binary search for the smallest t
    int low = 0, high = INT_MAX;
    while (low < high) {
        int mid = low + (high-low)/2;
        // Regresent the model as a bipartite graph with all the agents as nodes in one side, and
        // all the shelters duplicated for each possible capacity and then compute the maximum
        // cardinality matching
        Graph GG(a + s*c);
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < s; j++) {
                if (T[i][j] == INT_MAX) continue;
                for (int k = 0; k < c; k++) {
                    if (T[i][j] + (k + 1) * d <= mid) {
                        add_edge(i, a + k * s + j, GG);
                    }
                }
            }
        }
        // Compute maximum cardinality
        vector<Vertex> matemap(a + s * c); // Use as an Exterior Property Map: Vertex -> Matc
        edmonds_maximum_cardinality_matching (
            GG,
            make_iterator_property_map(matemap.begin(), get(vertex_index , G))
        );
        const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();
        int matchingsize = 0;
        for (int i = 0; i < a; i++) {
            matchingsize += (matemap[i] != NULL_VERTEX);
        }

        if (matchingsize == a) high = mid;
        else low = mid + 1;

    }
    cout << low << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        oh_her_majestys_secret_service();
    }
}
