#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>                   Triangulation;
typedef Triangulation::Finite_faces_iterator                FaceIt;
typedef Triangulation::Edge_iterator                        EdgeIt;
typedef Triangulation::Finite_vertices_iterator             VertexIt;
typedef Triangulation::Face_handle                          FaceH;
typedef Triangulation::Vertex_handle                        VertexH;
typedef K::Point_2                                          P;
typedef K::Segment_2                                        S;

using namespace std;


void light_the_stage() {
    int m, n, h;
    cin >> m >> n;

    vector<P> p(m), l(n);
    vector<int> r(m);

    // Read input
    long x, y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        p[i] = P(x, y);
        cin >> r[i];
    }
    cin >> h;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        l[i] = P(x, y);
    }

    // Create triangulation for the lamps points
    Triangulation tri;
    tri.insert(p.begin(), p.end());

    // Iterate over all the lamps
    vector<bool> w(m, true);  // w is the vector of winners

    K::FT d_2; int d_min;
    for (int i = 0; i < m; i++) {
        P n_l = tri.nearest_vertex(p[i])->point();
        d_2 = CGAL::squared_distance(n_l, p[i]);
        d_min = (r[i] + h) * (r[i] + h);
        if (d_2 < d_min) w[i] = false;
    }
    cout << endl;

    // Print result
    for (int i = 0; i < m; i++) {
        if (w[i]) cout << i << " ";
    }
    cout << endl;
}


int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        light_the_stage();
    }
}
