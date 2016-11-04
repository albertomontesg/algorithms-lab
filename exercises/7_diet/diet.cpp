#include <iostream>
#include <cassert>
#include <cmath>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>

// choose exact integral type
typedef CGAL::Gmpzf ET;

// program and solution types
typedef CGAL::Quadratic_program<long> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void diet(int n, int m){
    Program lp (CGAL::LARGER, true, 0, false, 0);


    for (int i = 0; i < n; i++) {
        long c_min, c_max;
        cin >> c_min >> c_max;

        lp.set_b(i*2, c_min);
        lp.set_b(i*2+1, c_max);
        lp.set_r(i*2+1, CGAL::SMALLER);
    }

    for (int j = 0; j < m; j++) {
        long p; cin >> p;
        lp.set_c(j, p);
        for (int i = 0; i < n; i++) {
            long C; cin >> C;
            lp.set_a(j, i*2, C);
            lp.set_a(j, i*2+1, C);
        }
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    assert (s.solves_linear_program(lp));

    if (s.is_infeasible() || s.is_unbounded()) {
        cout << "No such diet." << endl;
    } else {
        long result = floor(CGAL::to_double(s.objective_value()));
        cout << result << endl;
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    while (!(n==0 && m==0)) {
        diet(n, m);
        cin >> n >> m;
    }
}
