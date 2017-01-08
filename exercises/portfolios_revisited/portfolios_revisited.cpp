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
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;


void portfolios(int n, int m){

    // Quadratic Programming
    Program qp(CGAL::SMALLER, true, 0, false, 0);
    const int COST = 0;
    const int RETURN = 1;
    int c, r, v;
    vector<int> returns(n);

    qp.set_r(RETURN, CGAL::LARGER);
    for (int i = 0; i < n; i++) {
        cin >> c >> r;
        qp.set_a(i, COST, c);
        qp.set_a(i, RETURN, r);
        returns[i] = r;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> v;
            if (j <= i) qp.set_d(i, j, 2*v);
        }
    }
    for (int i = 0; i < m; i++) {
        long C, V;
        cin >> C >> V;

        qp.set_b(COST, C);

        int lower = 0, upper = INT_MAX, middle;
        double best_return = 0;
        // Binary search
        while (lower + 1 != upper) {
            middle = lower + (upper - lower) / 2;
            qp.set_b(RETURN, middle);

            Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());
            if (s.is_optimal() && CGAL::to_double(s.objective_value()) <= V) {
                lower = middle;
                // Compute return
                double total_return = 0;
                int indx = 0;
                for (auto it = s.variable_values_begin(); it != s.variable_values_end(); it++) {
                    total_return += returns[indx++] * CGAL::to_double(*it);
                }
                best_return = max(best_return, total_return);
            } else {
                upper = middle;
            }
        }
        cout << best_return << endl;
    }


}


int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) { break; }
        portfolios(n, m);
    }
}
