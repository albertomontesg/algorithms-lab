
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
#include <boost/graph/biconnected_components.hpp>


// Namespaces
using namespace std;
namespace boost {
    struct edge_component_t {
        enum { num = 555 };
        typedef edge_property_tag kind;
    } edge_component;
}

using namespace boost;

// Directed graph with integer weights on edges.
typedef adjacency_list<vecS, vecS, undirectedS, no_property, property <edge_component_t, size_t> > Graph;
typedef graph_traits<Graph>::vertex_descriptor      Vertex;
typedef graph_traits<Graph>::edge_descriptor        Edge;
typedef graph_traits<Graph>::edge_iterator          EdgeIt;


void important_bridges() {
    int n, m;
    cin >> n >> m;

    Graph G;
    vector<pair<int, int> > bridges(m), critical_bridges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        bridges[i] = pair<int, int>(u, v);
        Edge e; bool success;
        tie(e, success) = add_edge(u, v, G);
    }

    property_map<Graph, edge_component_t>::type
    component = get(edge_component, G);

    size_t num_comps = biconnected_components(G, component);

    // Agrupate all the Edges depending the component ID
    EdgeIt ei, ei_end;
    vector<vector<Edge> > edge_components(num_comps, vector<Edge>(0));
    for (tie(ei, ei_end) = edges(G); ei != ei_end; ++ei) {
        int comp = component[*ei];
        edge_components[comp].push_back(*ei);
    }

    // Store as result all the edges that are alone at its component
    for (int i = 0; i < num_comps; i++) {
        if (edge_components[i].size() > 1) {
            continue;
        }
        Vertex s, t;
        s = source(edge_components[i][0], G);
        t = target(edge_components[i][0], G);
        if (s < t) {
            critical_bridges.push_back(pair<int, int>(s, t));
        } else {
            critical_bridges.push_back(pair<int, int>(t, s));
        }
    }

    // Print number of critical bridges
    sort(critical_bridges.begin(), critical_bridges.end());
    cout << critical_bridges.size() << endl;
    for (int i = 0; i < critical_bridges.size(); i++) {
        cout << critical_bridges[i].first << " " << critical_bridges[i].second << endl;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        important_bridges();
    }
}
