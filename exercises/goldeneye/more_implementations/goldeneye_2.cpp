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
typedef Triangulation::Finite_edges_iterator                        EdgeIt;
typedef Triangulation::Face                                         Face;
typedef Triangulation::Face_handle                                  FaceH;
typedef Triangulation::Vertex_handle                                VertexH;
typedef K::Point_2                                                  Point;
typedef K::Segment_2                                                Segment;
typedef K::Triangle_2                                               Triangle;


Graph build_graph(Triangulation& t, int w) {
    // Build a graph given the w power consumption checking the distances between vertex adding
    // edges if the w value allows it
    int n = t.number_of_vertices();
    Graph G(n);

    Edge e; bool success;
    EdgeIt ei;
    FaceIt ft;
    map<Edge, bool> edge_seen;
    VertexH vh_a, vh_b;
    for ( ei = t.finite_edges_begin(); ei != t.finite_edges_end(); ei++ ) {
        Face f = *(ei->first);
        int i = ei->second;
        VertexH vs, vt;
        vs = f.vertex(f.cw(i));
        vt = f.vertex(f.ccw(i));
        K::FT d = CGAL::squared_distance(vs->point(), vt->point());
        if ( d <= w ) {
            tie(e, success) = add_edge(vs->info(), vt->info(), G);
        }

    }

    return G;

}

bool check_mission(Triangulation& tri, vector<pair<Point, int> >& j, vector<int>& component,
        Point s, Point t, int w) {
    int a = tri.nearest_vertex(s)->info();
    int b = tri.nearest_vertex(t)->info();

    int d1 = CGAL::squared_distance(s, j[a].first);
    int d2 = CGAL::squared_distance(t, j[b].first);

    if (d1 > w/4 || d2 > w/4) return false;
    else if (component[a] == component[b]) return true;
    else return false;
}

int binary_search(Triangulation& tri, vector<pair<Point, int> >& j,
        vector<Point>& s, vector<Point>& t) {


    return 0;
}

int evaluate(Triangulation& tri, vector<pair<Point, int> >& j, int w, vector<Point>& s, vector<Point>& t) {
    Graph G = build_graph(tri, w);
    int m = s.size(), n = j.size();

    // Compute the connected components
    vector<int> component(n);
    connected_components(G, &component[0]);

    // Check all the missions
    int missions_completed = 0;
    for (int i = 0; i < m; i++) {
        bool cm = check_mission(tri, j, component, s[i], t[i], w);
        if (cm) missions_completed |= 1<<i;
    }

    return missions_completed;
}

void goldeneye() {
    int n, m, p;
    cin >> n >> m >> p;

    // Define variables
    vector<pair<Point, int> > j(n);
    vector<Point> s(m), t(m);
    long x, y;
    // Read input data
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        j[i] = make_pair(Point(x, y), i);
    }
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        s[i] = Point(x, y);
        cin >> x >> y;
        t[i] = Point(x, y);
    }

    Triangulation tri;
    tri.insert(j.begin(), j.end());

    int missions_completed = evaluate(tri, j, p, s, t);
    for (int i = 0; i < m; i++) {
        if ((missions_completed & 1<<i) != 0) cout << "y";
        else cout << "n";
    }
    cout << endl;





    cout << "\n";
    cout << "\n";



}


int main() {
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        goldeneye();
    }
}
