
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <cmath>
#include <limits>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

using namespace std;

double floor_to_double(const K::FT& x) {
    double a = floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

void print_point(const P& p) {
    cout << fixed << setprecision(0) << floor_to_double(p.x()) << " " << floor_to_double(p.y()) << "\n";
}

void compute_firsthit(int n) {
    long x, y, a, b;
    cin >> x >> y >> a >> b;
    P xy(x, y), ab(a, b);
    R ray(xy, ab);

    bool hit = false;
    P hit_point;
    for (int i = 0; i < n; i++) {
        long r, s, t, u;
        cin >> r >> s >> t >> u;
        P rs(r, s), tu(t, u);
        S seg(rs, tu);

        if (CGAL::do_intersect(ray, seg)) {
            P intersect;
            auto o = CGAL::intersection(ray, seg);
            if (const P* op = boost::get<P>(&*o)) {
                intersect = *op;
            } else if (const S* se = boost::get<S>(&*o)) {
                intersect = (CGAL::has_smaller_distance_to_point(ray.source(), se->source(), se->target())) ? se->source() : se->target();
            }
            if (!hit) {
                hit = true;
                hit_point = intersect;
            } else if (CGAL::has_smaller_distance_to_point(ray.source(), intersect, hit_point)) {
                hit_point = intersect;
            }
        }
    }

    if (hit) {
        print_point(hit_point);
    } else {
        cout << "no" << endl;
    }

}


int main() {
    int nb_obstacles; cin >> nb_obstacles;

    while(nb_obstacles > 0) {
        compute_firsthit(nb_obstacles);
        cin >> nb_obstacles;
    }
    return 0;
}
