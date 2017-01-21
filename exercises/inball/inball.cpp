#include <iostream>
#include <cassert>
#include <cmath>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<long> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;


void inball(int n){
    int d; cin >> d;

    Program lp (CGAL::SMALLER, false, 0, false, 0);
    lp.set_c(d, -1);
    lp.set_l(d, true, 0);
    for (int i = 0; i < n; i++) {
        long norm = 0;
        for (int j = 0; j < d; j++) {
            long a; cin >> a;
            lp.set_a(j, i, a);
            norm += a * a;
        }
        lp.set_a(d, i, sqrt(norm));
        long b; cin >> b;
        lp.set_b(i, b);
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    assert (s.solves_linear_program(lp));

    if (s.is_infeasible()) {
        cout << "none" << endl;
    } else if (s.is_unbounded()) {
        cout << "inf" << endl;
    } else {
        long result = -CGAL::to_double(s.objective_value());
        cout << result << endl;
    }
}


int main() {
    int n;
    while (true) {
        cin >> n;
        if (n == 0) { break; }
        inball(n);
    }
}
