#include <iostream>
#include <vector>
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


bool solve(vector<vector<vector<long> > >& coefficients, const int h, const int t, const int d) {

    int nb_coeff = coefficients[0][d].size();

    Program lp (CGAL::SMALLER, false, 0, false, 0);
    CGAL::Quadratic_program_options options;
    options.set_pricing_strategy(CGAL::QP_BLAND);     // Bland's rule

    for (int i = 0; i < (h + t); i++) {
        for (int k = 0; k < nb_coeff; k++) {
            lp.set_a(k, i, coefficients[i][d][k]);
        }
        lp.set_b(i, 0);

        if (i >= h) lp.set_a(nb_coeff, i, 1); // Epsilon
    }
    lp.set_c(nb_coeff, -1);
    lp.set_l(nb_coeff, true, 0);

    Solution s = CGAL::solve_linear_program(lp, ET(), options);
    return s.is_unbounded();
}


void radiation(){
    int h, t;
    cin >> h >> t;

    const int D = 30;

    vector<vector<long> > health(h, vector<long>(3)), tumor(t,vector<long>(3));

    for (int i = 0; i < h; i++) cin >> health[i][0] >> health[i][1] >> health[i][2];
    for (int i = 0; i < t; i++) cin >> tumor[i][0] >> tumor[i][1] >> tumor[i][2];

    if (h == 0 || t == 0) {
        cout << 0 << endl;
        return;
    }

    vector<vector<vector<long> > >coefficients(h+t, vector<vector<long> >(D+1));

    for (int i = 0; i < (h + t); i++) {
        vector<long> cell = (i < h) ? health[i]: tumor[i-h];

        for (int d = 1; d <= D; d++) {
            long coef_x = 1;
            for (int x = 0; x <= d; x++) {
                long coef_y = 1;
                for (int y = 0; y <= d; y++) {
                    long coef_z = 1;
                    for (int z = 0; z <= d; z++) {
                        if (x + y + z > d) continue;
                        if (i >=h) coefficients[i][d].push_back(coef_x * coef_y * coef_z);
                        else coefficients[i][d].push_back(-coef_x * coef_y * coef_z);
                        coef_z *= cell[2];
                    }
                    coef_y *= cell[1];
                }
                coef_x *= cell[0];
            }
        }
    }

    // int low = 1;
    // int upper = 1
    // while (upper < D && !solve(coefficients, h, t, upper)) upper = min (2*upper, D);
    //
    // if (upper == 30)

    int upper = 1;
    bool solvable = solve(coefficients, h, t, upper);
    while (upper < D && !solvable) {
        upper *= 2;
        upper = min(upper, D);
        solvable = solve(coefficients, h, t, upper);
    }

    if (upper == D && !solvable) {
        cout << "impossible" << endl;
        return;
    }

    int low = upper / 2;
    while (low + 1 != upper) {
        int mid = low + (upper - low) / 2;
        if (solve(coefficients, h, t, mid)) {
            upper = mid;
        } else low = mid;
    }

    cout << upper << endl;
}


int main() {
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        radiation();
    }
}
