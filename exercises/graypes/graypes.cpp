#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>                   Triangulation;
typedef Triangulation::Finite_faces_iterator                Face_iterator;
typedef Triangulation::Edge_iterator                        EdgeIt;

using namespace std;


double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a+1 >= x) a -= 1;
    while (a < x) a += 1;
    return a;
}

void graypes(int n) {
    vector<K::Point_2> p(n);
    Triangulation t;

    for (int i = 0; i < n; i++) {
        long x, y;
        cin >> x >> y;
        p[i] = K::Point_2(x, y);
    }
    t.insert(p.begin(), p.end());

    K::FT min_dist = t.segment(t.finite_edges_begin()).squared_length();
    for (EdgeIt e = t.finite_edges_begin(); e != t.finite_edges_end(); e++) {
        min_dist = min(min_dist, t.segment(e).squared_length());
    }

    K::FT d = sqrt(min_dist * (100 * 100) / (2 * 2));

    cout << ceil_to_double(d) << endl;
}


int main() {
    int n;
    cout << fixed << setprecision(0);
    while (true) {
        cin >> n;
        if (n == 0) { break; }
        graypes(n);
    }
}
