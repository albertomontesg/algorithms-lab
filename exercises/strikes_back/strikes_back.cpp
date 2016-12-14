#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

// LP
typedef CGAL::Gmpzf ET;
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
// Delaunay
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>                   Triangulation;
typedef K::Point_2                                          Point;

using namespace std;

void strikes_back() {
    int a, s, b, e;
    cin >> a >> s >> b >> e;

    vector<Point> asteroid(a), shooting_points(s), bounty_hunters(b);
    vector<int> asteroid_densities(a);
    long x, y;
    // Read data
    for (int i = 0; i < a; i++) {
        cin >> x >> y;
        asteroid[i] = Point(x, y);
        cin >> asteroid_densities[i];
    }
    for (int i = 0; i < s; i++) {
        cin >> x >> y;
        shooting_points[i] = Point(x, y);
    }
    for (int i = 0; i < b; i++) {
        cin >> x >> y;
        bounty_hunters[i] = Point(x, y);
    }

    // Create a triangulation for the bounty hunters to find the closest one at each shooting point
    Triangulation bh;
    bh.insert(bounty_hunters.begin(), bounty_hunters.end());

    // Initialize linear program
    Program lp (CGAL::LARGER, true, 0, false, 0);

    double max_d = LONG_MAX;    // Distance to the closest bounty hunters
    double d;
    for (int i = 0; i < s; i++) {
        if (b > 0) {            // In case the set ob bounty hunters are empty
            Point cl_bh = bh.nearest_vertex(shooting_points[i])->point();
            max_d = CGAL::to_double(CGAL::squared_distance(cl_bh, shooting_points[i]));
        }

        for (int j = 0; j < a; j++) {
            // Compute the distance of every shooting point to each asteroid
            d = CGAL::to_double(CGAL::squared_distance(shooting_points[i], asteroid[j]));
            // If the closests bounty hunter is nearer than the asteroid, then to this no energy
            // will arrive
            if(d >= max_d) continue;

            // If arrives compute the coefficient
            double coef = 1 / ((double) max(1., d));
            lp.set_a(i, j, coef);
        }
        lp.set_c(i, 1);         // Minimize the sum of energy at each shot
        lp.set_a(i, a, 1);      // (*) Set a last inequality upbounding the total amount of energy
                                // used
    }
    lp.set_b(a, e);                 // (*)
    lp.set_r(a, CGAL::SMALLER);     // (*)
    // Set a lower limit to the amount of energy that must arrive to each asteroid
    for (int j = 0; j < a; j++) {
        lp.set_b(j, asteroid_densities[j]);
    }

    // Solve LP
    Solution sol = CGAL::solve_linear_program(lp, ET());
    assert (sol.solves_linear_program(lp));

    // If exists solution then its possible to do it
    if (sol.is_optimal()) cout << "y" << endl;
    else cout << "n" << endl;

}

int main() {
    int T; cin >> T;
    for (int i = 0; i < T; i++) {
        strikes_back();
    }
}
