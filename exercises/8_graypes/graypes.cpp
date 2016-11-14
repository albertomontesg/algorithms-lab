#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>                   Triangulation;
typedef Triangulation::Finite_faces_iterator                Face_iterator;

using namespace std;


double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a+1 >= x) a -= 1;
    while (a < x) a += 1;
    return a;
}

void graypes(int n) {
    vector<K::Point_2> p(n-1);
    Triangulation t;

    long x, y; cin >> x >> y;
    K::Point_2 p_q(x, y);
    for (int i = 0; i < n-1; i++) {
        long x, y;
        cin >> x >> y;
        p[i] = K::Point_2(x, y);
    }

    t.insert(p.begin(), p.end());
    K::Point_2 n_p =  t.nearest_vertex(p_q)->point();
    t.remove(t.nearest_vertex(p_q));

    K::FT d;
    if (t.number_of_vertices() == 0) {
        d = sqrt(CGAL::squared_distance(n_p, p_q)) * 100 / 2 ;
    } else if (CGAL::squared_distance(p_q,n_p) < CGAL::squared_distance(n_p, t.nearest_vertex(n_p)->point())) {
        d = sqrt(CGAL::squared_distance(n_p, p_q)) * 100 / 2 ;
    } else {
        cout << p_q << "\t" << n_p;
        d = sqrt(CGAL::squared_distance(n_p, p_q)) * 0 / 2 ;
    }

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
