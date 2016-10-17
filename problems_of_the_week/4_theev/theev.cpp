
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <vector>
#include <set>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

using namespace std;


double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a+1 >= x) a -= 1;
    while (a < x) a += 1;
    return a;
}

void theev() {
    int n; cin >> n;

    // Read cities locations
    long x, y; cin >> x >> y;
    P their_city(x,y);

    vector<P> cities(n);
    for (int i = 1; i < n; i++) {
        long x, y;
        cin >> x >> y;
        cities[i] = P(x, y);
    }

    K::FT tc_radius(0);
    K::FT ex_radius(0);

    vector<P> c(1);
    c[0] = cities[0];

    P ex_center = c[0];

    set<pair<K::FT, P>, std::greater<pair<K::FT, P> > > distances_to_TC;
    for (int i = 1; i < n-1; i++) {
        P point = cities[i];
        K::FT d_tc = CGAL::squared_distance(point, their_city);
        K::FT d_ex = CGAL::squared_distance(point, ex_center);
        if (d_tc <= d_ex) {
            // Add point to the TC transmissor
            if (d_tc > tc_radius) {
                tc_radius = d_tc;
            }
        } else {
            c.push_back(point);
            Min_circle mc(c.begin(), c.end(), true);
            Traits::Circle circle = mc.circle();
            ex_center = circle.center();
            ex_radius = circle.squared_radius();

            Min_circle all_mc(c.begin(), c.begin()+i-1, true);


        }
        // Add all the closest points from the external circle to the TC
        auto start = distances_to_TC.begin();
        while (start != distances_to_TC.end()) {
            if (CGAL::squared_distance(start->second, their_city) <= CGAL::squared_distance(start->second, ex_center)) {
                distances_to_TC.erase(start);
            }
            start++;
        }
    }

    cout << min(ceil_to_double(tc_radius), ceil_to_double(ex_radius)) << endl;

}


int main() {
    int t; cin >> t;

    cout << fixed << setprecision(0);
    for (int i = 0; i < t; i++) {
        theev();
    }
    return 0;
}
