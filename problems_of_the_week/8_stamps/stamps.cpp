#include <vector>
#include <cmath>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// Choose exact integral type
typedef CGAL::Gmpzf ET;
// Program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
// Geometric types
typedef CGAL::Exact_predicates_exact_constructions_kernel   K;
typedef K::Point_2                                          P;
typedef K::Segment_2                                        S;

using namespace std;


void stamps() {
    int l, s, w; cin >> l >> s >> w;

    vector<P> lamps(l), stamps(s);
    vector<long> M(s);
    vector<S> walls(w);

    // Read data
    for (int i = 0; i < l; i++) {
        long x, y; cin >> x >> y;
        lamps[i] = P(x, y);
    }
    for (int i = 0; i < s; i++) {
        long x, y;
        cin >> x >> y; stamps[i] = P(x, y);
        cin >> M[i];
    }
    for (int i = 0; i < w; i++) {
        long x_a, y_a, x_b, y_b;
        cin >> x_a >> y_a >> x_b >> y_b;
        walls[i] = S(P(x_a, y_a), P(x_b, y_b));
    }

    // Define quadratic program
    Program lp (CGAL::SMALLER, true, 1, true, 1<<12);
    for (int i = 0; i < s; i++) {               // stamp index
        for (int j = 0; j < l; j++) {           // lamp index
            S l_s(lamps[j], stamps[i]);         // lamp to stamp segment

            bool blocked = false;
            for (int k = 0; k < w; k++) {
                if (CGAL::do_intersect(walls[k], l_s)) {
                    blocked = true;
                    break;
                }
            }

            if (!blocked) {
                double d = CGAL::to_double(1 / l_s.squared_length());
                lp.set_a(j, i, d);
                lp.set_a(j, i+s, d);
            }
        }
        lp.set_b(i, M[i]);
        lp.set_r(i, CGAL::SMALLER);
        lp.set_b(s+i, 1);
        lp.set_r(s+i, CGAL::LARGER);
    }

    // Get solution
    Solution sol = CGAL::solve_linear_program(lp, ET());
    assert (sol.solves_linear_program(lp));

    if (sol.is_infeasible()) {
        cout << "no" << endl;
    } else {
        cout << "yes" << endl;
    }

}


int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        stamps();
    }
}
