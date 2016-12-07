#include <vector>
#include <map>
#include <stack>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;


typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property>   Graph;
typedef graph_traits<Graph>::edge_descriptor                                Edge;
typedef graph_traits<Graph>::vertex_descriptor                              Vertex;

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

    Triangulation t;
    t.insert(s.begin(), s.end());
    FaceIt ft; bool interferance = false;
    vector<int> fc(t.number_of_faces()); // Store for each face, how many edges have length < r^2

    EdgeIt ei;
    map<Edge, bool> edge_seen;
    for (ft = t.finite_faces_begin(); ft != t.finite_faces_end(); ft++) {
        Triangle tr = t.triangle(ft);
        int count = 0;
        for (int j = 0; j < 3; j++) {
            K::FT d = CGAL::squared_distance(tr[j], tr[(j+1)%3]);
            if (d <= r*r) count++;
        }
        if (count > 2) interferance = true;
    }

    for (int i = 0; i < m; i++) {
        if (interferance) cout << "n";
        else cout << "y";
    }
    cout << endl;

}


int main() {
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        clues();
    }
}
