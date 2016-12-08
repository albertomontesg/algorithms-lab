#include <vector>
#include <map>
#include <stack>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

using namespace std;
using namespace boost;

// BGL typedefs
typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property>   Graph;
typedef graph_traits<Graph>::edge_descriptor                                Edge;
typedef graph_traits<Graph>::vertex_descriptor                              Vertex;
// CGAL typedefs
typedef CGAL::Exact_predicates_inexact_constructions_kernel         K;
typedef CGAL::Triangulation_vertex_base_with_info_2<unsigned, K>    Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>                    Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                      Triangulation;
typedef Triangulation::Finite_faces_iterator                        FaceIt;
typedef Triangulation::Edge_iterator                                EdgeIt;
typedef Triangulation::Face_handle                                  FaceH;
typedef Triangulation::Vertex_handle                                VertexH;
typedef K::Point_2                                                  Point;
typedef K::Segment_2                                                Segment;
typedef K::Triangle_2                                               Triangle;


void clues() {
    int n, m, r;
    cin >> n >> m >> r;

    vector<pair<Point, unsigned> > s; s.reserve(n);
    vector<Point> a(m), b(m);
    long x, y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        s.push_back(make_pair(Point(x, y), i));
    }
    for (int i = 0; i < m; i++) {
        cin >> x >> y; a[i] = Point(x, y);
        cin >> x >> y; b[i] = Point(x, y);
    }

    // Define the triangulation
    Triangulation t;
    t.insert(s.begin(), s.end());
    FaceIt ft; bool interference = false;

    // Define the graph
    Graph G(n);
    Edge e; bool success;

    // Iterate over all faces and see how many of triangles, all the edges are shorter than r so
    // interferance is caused
    EdgeIt ei;
    map<Edge, bool> edge_seen;
    VertexH vh_a, vh_b;
    for (ft = t.finite_faces_begin(); ft != t.finite_faces_end(); ft++) {
        int count = 0;
        for (int j = 0; j < 3; j++) {
            vh_a = ft->vertex(j); vh_b = ft->vertex((j+1)%3);
            K::FT d = CGAL::squared_distance(vh_a->point(), vh_b->point());
            if ( d <= r*r ) {
                tie(e, success) = add_edge(vh_a->info(), vh_b->info(), G);
                count++;
            }
        }
        if (count > 2) interference = true;
    }
    // In the case the triangulation doesn't make any finite triangle (1 or 2 vertex)
    if (n == 2) {
        // Only with two vertex is required to create an edge at the graph only if the distance
        // is enough
        if ( CGAL::squared_distance(s[0].first, s[1].first) <= r*r )
            tie(e, success) = add_edge(0, 1, G);
    }

    // Compute the connected components
    vector<int> component(n);
    connected_components(G, &component[0]);

    int v_a, v_b, d_a, d_b, d_ab;
    for (int i = 0; i < m; i++) {
        // Check the interferance previously computed from the triangulation
        if ( interference ) {
            cout << "n";
            continue;
        }

        // Search the nearest nodes to connect from a_i to b_i
        v_a = t.nearest_vertex(a[i])->info();
        v_b = t.nearest_vertex(b[i])->info();
        // Compute the distances to check reachability
        d_a = CGAL::squared_distance(s[v_a].first, a[i]);
        d_b = CGAL::squared_distance(s[v_b].first, b[i]);
        d_ab = CGAL::squared_distance(a[i], b[i]);
        if ( d_ab <= r*r ) {
            cout << "y";
            continue;
        } else if ( d_a > r*r || d_b > r*r ) {
            cout << "n";
            continue;
        }

        // Now check if the nodes which are connected a and b are in the same graph component
        if (component[v_a] == component[v_b]) cout << "y";
        else cout << "n";
    }
    cout << endl;

}


int main() {
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        clues();
    }
}
