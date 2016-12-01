// Includes
// ========
// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/connected_components.hpp>
// CGAL
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

// Namespaces
using namespace std;
using namespace boost;

// Directed graph with integer weights on edges.
typedef adjacency_list<vecS, vecS, undirectedS,
    no_property, property<edge_weight_t, int> >         Graph;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;	// Vertex type
typedef graph_traits<Graph>::edge_descriptor            Edge;	// Edge type
typedef graph_traits<Graph>::edge_iterator              EdgeIt;	// Edge iterator
// Property map edge -> weight
typedef property_map<Graph, edge_weight_t>::type        WeightMap;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                                          P;

typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>  Vb;
typedef CGAL::Triangulation_face_base_2<K>                  Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>         Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>               Triangulation;
typedef Triangulation::Edge_iterator                        Edge_iterator;
typedef Triangulation::Vertex_handle                        VertexH;

int get_k_planets(int t, vector<pair<P, int> >& planets, const int r, const int n) {
    assert(t > 0);
    assert(t < n);
    int n_not_conquered = n - t;

    Graph G(n_not_conquered);

    Triangulation tr;
    tr.insert(planets.begin(), planets.begin() + n_not_conquered);

    for (Edge_iterator e = tr.finite_edges_begin(); e != tr.finite_edges_end(); e++) {
        VertexH v1 = e->first->vertex((e->second + 1) % 3);
        VertexH v2 = e->first->vertex((e->second + 2) % 3);
        if (CGAL::squared_distance(v1->point(), v2->point()) <= r*r) {
            add_edge(v1->info(), v2->info(), G);
        }
    }

    // Analyze components
    vector<int> component(num_vertices(G));
    int n_components = connected_components(G, &component[0]);
    vector<int> sizes(n_components, 0);
    int largest = -1;
    for (int i = 0; i < n_not_conquered; i++) {
        int c = component[i];
        sizes[c]++;
        largest = max(largest, sizes[c]);
    }

    return min(t, largest);
}

int search_t(int begin, int end, vector<pair<P, int> >& planets, const int r, const int n) {
    // cout << begin << " " << end;
    if (begin == end) return get_k_planets(begin, planets, r, n);
    else if (begin + 1 == end)
        return max(get_k_planets(begin, planets, r, n), get_k_planets(end, planets, r, n));
    else {
        int middle = (begin + end) / 2;
        int b = get_k_planets(middle, planets, r, n);
        if (b == middle) return search_t(middle, end, planets, r, n);
        else return search_t(begin, middle, planets, r, n);
    }
}

void sith() {
    int n, r; cin >> n >> r;

    vector<pair<P, int> > p(n);
    long x, y;
    for (int i = n-1; i >= 0; i--) {
        cin >> x >> y;
        p[i] = make_pair(P(x, y), i);
    }
    int t = search_t(0, n, p, r, n);
    cout << t << endl;

}

int main() {
    int T; cin >> T;
    for (int t = 0; t < T; t++){
        sith();
    }
}
