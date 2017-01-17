
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <iostream>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;

using namespace std;


void compute_hit(int n) {
    long x, y, a, b;
    cin >> x >> y >> a >> b;
    K::Point_2 xy(x, y), ab(a, b);
    K::Ray_2 ray(xy, ab);

    bool hit = false;
    for (int i = 0; i < n; i++) {
        long r, s, t, u;
        cin >> r >> s >> t >> u;
        if (hit) {
            continue;
        }
        K::Point_2 rs(r, s), tu(t, u);
        K::Segment_2 seg(rs, tu);
        if (CGAL::do_intersect(ray, seg)) {
            hit = true;
        }
    }

    string result = (hit) ? "yes" : "no";
    cout << result << endl;

}


int main() {
    ios_base::sync_with_stdio(false);
    int nb_obstacles; cin >> nb_obstacles;

    while(nb_obstacles > 0) {
        compute_hit(nb_obstacles);
        cin >> nb_obstacles;
    }
    return 0;
}
