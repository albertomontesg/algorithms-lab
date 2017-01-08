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


bool solve(vector<vector<long> >& health, vector<vector<long> >& tumor, const int D) {
    int h = health.size(), t = health.size();

    Program lp (CGAL::SMALLER, false, 0, false, 0);
    CGAL::Quadratic_program_options options;
    options.set_pricing_strategy(CGAL::QP_BLAND);     // Bland's rule

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < 3; j++) {
            for (int d = 1; d <= D; d++) {
                lp.set_a(i, j*3+d-1, health[i][j]^d);
            }
        }
        lp.set_a(i, D*3, 1);    // Epsilon

        lp.set_b(i, 0);
        lp.set_u(i, CGAL::LARGER);
    }

    for (int i = 0; i < t; i++) {
        for (int j = 0; j < 3; j++) {
            for (int d = 1; d <= D; d++) {
                lp.set_a(i, j*3+d, tumor[i][j]^d);
            }
        }
        lp.set_a(i, D*3, 1);    // Epsilon

        lp.set_b(i, 0);
        lp.set_u(i, CGAL::SMALLER);
    }
    lp.set_c(D*3, 1);

    Solution s = CGAL::solve_linear_program(lp, ET(), options);
    return !s.is_infeasible();
}


void radiation(){
    int h, t;
    cin >> h >> t;

    vector<vector<long> > health(h, vector<long>(3)), tumor(t,vector<long>(3));

    for (int i = 0; i < h; i++) cin >> health[i][0] >> health[i][1] >> health[i][3];
    for (int i = 0; i < t; i++) cin >> tumor[i][0] >> tumor[i][1] >> tumor[i][3];



}


int main() {
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        radiation();
    }
}
