#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel         K;
typedef CGAL::Triangulation_vertex_base_with_info_2<unsigned, K>    Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>                    Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                      Triangulation;
typedef Triangulation::Vertex_handle                                VertexH;
typedef K::Point_2                                                  P;
typedef K::Segment_2                                                S;

using namespace std;


void light_the_stage() {
    int m, n, h;
    cin >> m >> n;

    vector<P> l(n);
    vector<pair<P, unsigned> > p;
    p.reserve(m);
    vector<int> r(m);

    // Read input
    long x, y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        p.push_back(make_pair(P(x, y), i));
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
    for (int i = 0; i < n; i++) {
        VertexH v = tri.nearest_vertex(l[i]);
        unsigned idx = v->info();
        P n_p = p[idx].first;
        d_2 = CGAL::squared_distance(n_p, l[i]);
        d_min = (r[idx] + h) * (r[idx] + h);
        if (d_2 < d_min) {
            w[idx] = false;
            tri.remove(v);
        }
    }

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
