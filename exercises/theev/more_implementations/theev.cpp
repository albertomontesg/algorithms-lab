
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel   EK;
typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef IK::Point_2                                         P;
typedef EK::Point_2                                         eP;
typedef CGAL::Min_circle_2_traits_2<EK>                     Traits;
typedef CGAL::Min_circle_2<Traits>                          Min_circle;

using namespace std;


double ceil_to_double(const IK::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a + 1 >= x) a -= 1;
    while (a < x) a += 1;
    return a;
}

void theev() {
    int n; cin >> n;

    // Read cities locations
    long x, y; cin >> x >> y;
    P their_city(x,y);

    vector<P> cities(n-1);
    for (int i = 0; i < n-1; i++) {
        cin >> x >> y;
        cities[i] = P(x, y);
    }

    // For the cas we have one or two cities where the min radius will be 0
    if (n <= 2) {
        cout << 0 << endl;
        return;
    }

    sort(cities.begin(), cities.end(),
        [&their_city](P a, P b) {
        return CGAL::squared_distance(a, their_city) > CGAL::squared_distance(b, their_city);
        }
    );

    vector<IK::FT> distances(n-1);
    for (int i = 0; i < n - 1; i++) {
        distances[i] = squared_distance(cities[i], their_city);
    }

    IK::FT tc_radius = distances[1], tc_prev_radius = distances[1];
    IK::FT ex_radius = 0, ex_prev_radius = 0;

    // Initialize the external circle with the furthest city
    Min_circle min_ex_circle(eP(cities[0].x(), cities[0].y()));
    Traits::Circle circle = min_ex_circle.circle();

    int index = 1;

    while (ex_radius < tc_radius && index < n - 1) {
        tc_prev_radius = tc_radius;
        ex_prev_radius = ex_radius;

        min_ex_circle.insert(eP(cities[index].x(), cities[index].y()));
        circle = min_ex_circle.circle();

        tc_radius = distances[index + 1];
        ex_radius = IK::FT(CGAL::to_double(circle.squared_radius()));

        index++;
    }

    IK::FT result = min(
        max(tc_radius, ex_radius),
        max(tc_prev_radius, ex_prev_radius)
    );

    cout << ceil_to_double(result) << endl;

}


int main() {
    int t; cin >> t;

    cout << fixed << setprecision(0);
    for (int i = 0; i < t; i++) {
        theev();
    }
    return 0;
}
