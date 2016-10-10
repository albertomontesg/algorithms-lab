
#include <algorithm>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <vector>
#include <stdexcept>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Line_2 Line;
typedef K::Segment_2 Segment;
typedef K::Triangle_2 Triangle;

using namespace std;

void add_triangle(vector<int>& intersected, vector<Segment>& path, Triangle& t) {
    for (int i = 0; i < path.size(); i++) {
        if ( CGAL::do_intersect(path[i], t) ) {
            intersected[i]++;
        }
    }
}

void remove_triangle(vector<int>& intersected, vector<Segment>& path, Triangle& t) {
    for (int i = 0; i < path.size(); i++) {
        if ( CGAL::do_intersect(path[i], t) ) {
            intersected[i]--;
        }
    }
}

bool all_intersected(vector<int>& intersected) {
    return find(intersected.begin(), intersected.end(), 0) == intersected.end();
}

void compute_hiking_maps() {
    int m, n; cin >> m >> n;

    vector<Point> path_points(m);
    long x, y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        path_points[i] = Point(x, y);
    }
    vector<Segment> path(m-1);
    for (int i = 0; i < m-1; i++) {
        path[i] = Segment(path_points[i], path_points[i+1]);
    }

    vector<Triangle> maps(n);
    for (int i = 0; i < n; i++) {
        vector<Point> points(6);
        for (int j = 0; j < 6; j++) {
            cin >> x >> y;
            points[j] = Point(x, y);
        }

        vector<Line> lines(3);
        for (int j = 0; j < 3; j++) {
            lines[j] = Line(points[2*j], points[2*j+1]);
        }
        vector<Point> vertex(3);
        for (int j = 0; j < 3; j++) {
            auto o = CGAL::intersection(lines[j], lines[(j+1)%3]);
            if (const Point*op = boost::get<Point>(&*o)) {
                vertex[j] = *op;
            } else {
                throw runtime_error("At least should be a point to intersect");
            }
        }
        maps[i] = Triangle(vertex[0], vertex[1], vertex[2]);
    }

    vector<int> intersected(m, 0);
    int min_cost = 8000;
    int b = 0, e = 1;
    add_triangle(intersected, path, maps[b]);
    while (b < n && e < n-1) {
        if (all_intersected(intersected) && (e-b) < min_cost) {
            min_cost = e - b;
        }
        if (!all_intersected(intersected)) {
            add_triangle(intersected, path, maps[++e]);
        } else {
            remove_triangle(intersected, path, maps[b++]);
        }
    }
    cout << min_cost << endl;

}


int main() {
    int c; cin >> c;

    for (int i = 0; i < c; i++) {
        compute_hiking_maps();
    }
    return 0;
}
