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

bool solve_case(vector<long>& c, vector<long>& r, vector<vector<long> >& v, long C, long R, long V, int n) {
    Program qp (CGAL::LARGER, true, 0, false, 0);
    for (int i = 0; i < n; i++) {
        qp.set_a(i, 0, r[i]);
        qp.set_a(i, 1, c[i]);
    }
    qp.set_r(1, CGAL::SMALLER);
    qp.set_b(0, R);
    qp.set_b(1, C);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            qp.set_d(i, j, 2*v[i][j]);
        }
    }

    Solution s = CGAL::solve_quadratic_program(qp, ET());
    assert (s.solves_quadratic_program(qp));

    if (s.is_infeasible() || s.is_unbounded()) {
        return false;
    } else if (CGAL::to_double(s.objective_value()) <= V) {
        return true;
    } else {
        return false;
    }

}


void portfolios(int n, int m){
    vector<long> c(n), r(n);
    vector<vector<long> > v(n, vector<long>(n));

    for (int i = 0; i < n; i++) {
        cin >> c[i] >> r[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> v[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        long C, V, R;
        cin >> C >> R >> V;
        bool result = solve_case(c, r, v, C, R, V, n);
        if (result) {
            cout << "Yes." << endl;
        } else {
            cout << "No." << endl;
        }
    }


}


int main() {
    int n, m;
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) { break; }
        portfolios(n, m);
    }
}
