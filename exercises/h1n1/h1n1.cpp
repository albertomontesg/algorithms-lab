#include <vector>
#include <map>
#include <stack>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>                   Triangulation;
typedef Triangulation::Finite_faces_iterator                FaceIt;
typedef Triangulation::Edge_iterator                        EdgeIt;
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

void h1n1(int n) {

    vector<Point> infected(n);
    Triangulation t;
    int m;

    for (int i = 0; i < n; i++) {
        long x, y;
        cin >> x >> y;
        infected[i] = Point(x, y);
    }
    t.insert(infected.begin(), infected.end());

    cin >> m;
    for (int i = 0; i < m; i++) {
        long x, y, d;
        cin >> x >> y >> d;
        Point q(x, y);

        bool result = false;

        if (CGAL::squared_distance(q, t.nearest_vertex(q)->point()) < d) {
            cout << "n";
            continue;
        }

        FaceH face_1 = t.locate(q);

        map<FaceH, bool> face_seen;
        stack<FaceH> face_stack;

        face_stack.push(face_1);
        while(!face_stack.empty()) {
            FaceH face = face_stack.top();
            face_stack.pop();

            // If you are placed on an infinite face, as you are not closer from d to the nearest
            // point, you can escape from the infected
            if (t.is_infinite(face)) {
                result = true;
                break;
            }

            face_seen[face] = true;

            for (int j = 0; j < 3; j++) {
                Segment s = t.segment(face, j);

                // The point can not escape from this face through this edge of the triangulation
                if (s.squared_length() < d*4) { continue; }

                // If can scape through, take the neighbour face
                FaceH neighbour = face->neighbor(j);
                // If it has been seen continue
                if (face_seen[neighbour]) { continue; }
                // Put to the queue of faces to study if scapatory
                face_stack.push(neighbour);
            }
        }

        if (result) {
            cout << "y";
        } else {
            cout << "n";
        }

    }
    cout << endl;
}


int main() {
    int n;
    cout << fixed << setprecision(0);
    while (true) {
        cin >> n;
        if (n == 0) { break; }
        h1n1(n);
    }
}
