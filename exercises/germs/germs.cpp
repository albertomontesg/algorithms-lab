#include <vector>
#include <map>
#include <stack>
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
typedef K::Point_2                                          Point;
typedef K::Segment_2                                        Segment;

using namespace std;


double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a+1 >= x) a -= 1;
    while (a < x) a += 1;
    return a;
}

void germs(int n) {
    long l, b, r, t;
    cin >> l >> b >> r >> t;

    vector<Point> bacteries(n);
    vector<K::FT> distances(n);
    for (int i = 0; i < n; i++) {
        long x, y;
        cin >> x >> y;
        bacteries[i] = Point(x, y);
    }

    Triangulation tri;
    tri.insert(bacteries.begin(), bacteries.end());

    int i = 0;
    for (VertexIt vi = tri.finite_vertices_begin(); vi != tri.finite_vertices_end(); vi++) {
        VertexH vh = vi;
        Point p = vh->point();

        // Take the min distance to the neirest neighbour
        K::FT min_distance;
        if (tri.number_of_vertices() > 1) {
            VertexH vn = CGAL::nearest_neighbor(tri, vh);
            min_distance = CGAL::squared_distance(vh->point(), vn->point()) / 4;
        } else {
            // In the case the germ is alone, initialize min distance with the distance to one
            // corner (it will allways be greater than the distance to any of the boundaries)
            min_distance = CGAL::squared_distance(vh->point(), Point(l, b));
        }

        // check with every boundary if the distance is less than the minimum
        min_distance = min(min_distance, (p.x() - l) * (p.x() - l));
        min_distance = min(min_distance, (p.x() - r) * (p.x() - r));
        min_distance = min(min_distance, (p.y() - t) * (p.y() - t));
        min_distance = min(min_distance, (p.y() - b) * (p.y() - b));

        distances[i++] = min_distance;
    }

    sort(distances.begin(), distances.end());
    vector<double> dead_time(n);
    for (int i = 0; i < n; i++) {
        K::FT d = distances[i];
        long ti = ceil_to_double(sqrt(sqrt(d) - .5));
        dead_time[i] = ti;
    }

    // Print results
    cout << dead_time[0] << " " << dead_time[n/2] << " " << dead_time[n-1] << endl;

}


int main() {
    int n;
    cout << fixed << setprecision(0);
    while (true) {
        cin >> n;
        if (n == 0) { break; }
        germs(n);
    }
}
