#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef CGAL::Delaunay_triangulation_2<K>                       Triangulation;
typedef K::Point_2                                              P;

using namespace std;


void light_the_stage() {
    int m, n, h;
    cin >> m >> n;

    vector<P> l(n), p(m);
    vector<int> r(m);
    vector<int> dead_time(m, INT_MAX);

    // Read input
    int x, y;
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
    tri.insert(l.begin(), l.end());

    // Iterate over all participants and look for the closest lamp
    for (int i = 0; i < m; i++) {
        P v = tri.nearest_vertex(p[i])->point();
        double d_2 = CGAL::squared_distance(v, p[i]);
        double d = (r[i] + h);
        double d_max = d * d;

        if (d_max <= d_2) continue;
        
        for (int j = 0; j < n; j++) {
            double dist = CGAL::squared_distance(p[i], l[j]);
            if (d_max > dist) {
                dead_time[i] = j;
                break;
            }
        }
    }

    int winner_time = *std::max_element(dead_time.begin(), dead_time.end());

    // Print result
    for (int i = 0; i < m; i++) {
        if (dead_time[i] == winner_time) cout << i << " ";
    }
    cout << endl;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        light_the_stage();
    }
}
