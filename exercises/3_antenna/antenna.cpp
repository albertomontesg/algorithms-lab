
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

using namespace std;


double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a+1 >= x) a -= 1;
    while (a < x) a += 1;
    return a;
}

void compute_antenna_radius(int n) {
    vector<K::Point_2> P(n);
    long x, y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        P[i] = K::Point_2(x, y);
    }

    Min_circle mc(P.begin(), P.end(), true);
    Traits::Circle c = mc.circle();
    cout << ceil_to_double(sqrt(c.squared_radius())) << endl;
}


int main() {
    int nb_population; cin >> nb_population;

    cout << fixed << setprecision(0);
    while(nb_population > 0) {
        compute_antenna_radius(nb_population);
        cin >> nb_population;
    }
    return 0;
}
