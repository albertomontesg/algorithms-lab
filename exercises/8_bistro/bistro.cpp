#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>                   Triangulation;
typedef Triangulation::Finite_faces_iterator                Face_iterator;
typedef Triangulation::Edge_iterator                        EdgeIt;
typedef K::Point_2                                          Point;

using namespace std;


double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a+1 >= x) a -= 1;
    while (a < x) a += 1;
    return a;
}

void bistro(int n) {
    int m;
    vector<Point> r(n);
    Triangulation t;

    for (int i = 0; i < n; i++) {
        long x, y;
        cin >> x >> y;
        r[i] = Point(x, y);
    }
    t.insert(r.begin(), r.end());

    cin >> m;

    for (int i = 0; i < m; i++) {
        long x, y;
        cin >> x >> y;
        Point p = Point(x,y);
        K::FT dist = CGAL::squared_distance(p, t.nearest_vertex(p)->point());
        cout << ceil_to_double(dist) << endl;
    }

}


int main() {
    int n;
    cout << fixed << setprecision(0);
    while (true) {
        cin >> n;
        if (n == 0) { break; }
        bistro(n);
    }
}
