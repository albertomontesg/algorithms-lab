
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel   K;
typedef K::Point_2                                         P;
typedef K::Point_2                                         P;
typedef CGAL::Min_circle_2_traits_2<K>                     Traits;
typedef CGAL::Min_circle_2<Traits>                          Min_circle;

using namespace std;


double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a + 1 >= x) a -= 1;
    while (a < x) a += 1;
    return a;
}


pair<bool, K::FT> evaluate(int index, vector<K::FT>& distances, vector<P>& cities) {

    // Initialize the external circle with the furthest cities from 0 to index.
    Min_circle min_ex_circle(cities.begin(), cities.begin() + index + 1, true);
    Traits::Circle circle = min_ex_circle.circle();

    K::FT ex_radius = circle.squared_radius();
    K::FT tc_radius;
    if (index >= cities.size() - 1) tc_radius = 0;
    else tc_radius = distances[index + 1];

    bool eval = ex_radius >= tc_radius;
    K::FT max_radius = max(ex_radius, tc_radius);

    return make_pair(eval, max_radius);
}

int binary_search(int left, int right, vector<K::FT>& distances, vector<P>& cities) {
    if (left == right - 1) return left;
    int m = (right + left) / 2;

    K::FT max_rad; bool eval;
    tie(eval, max_rad) = evaluate(m, distances, cities);
    if (!eval) {
        return binary_search(m, right, distances, cities);
    } else {
        return binary_search(left, m, distances, cities);
    }
}

void theev() {
    int n; cin >> n;

    // Read cities locations
    long x, y; cin >> x >> y;
    P their_city(x, y);
    P e_their_city(x, y);

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

    // Sort all the cities depending on the distance to the capital with decreasing order
    sort(cities.begin(), cities.end(),
        [&their_city](P a, P b) {
            return CGAL::squared_distance(a, their_city) > CGAL::squared_distance(b, their_city);
        }
    );

    // Compute and store the distances to the capital
    vector<K::FT> distances(n-1);
    for (int i = 0; i < n - 1; i++) {
        distances[i] = squared_distance(cities[i], their_city);
    }

    // Perform binary search
    int index = binary_search(0, n-1, distances, cities);

    K::FT rad_1 = evaluate(index, distances, cities).second;
    K::FT rad_2 = evaluate(index + 1, distances, cities).second;

    K::FT result = min(rad_1, rad_2);

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
