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

void solve_1(int a, int b){
    Program qp (CGAL::SMALLER, true, 0, false, 0);
    const int X = 0;
    const int Y = 1;
    qp.set_a(X, 0, 1); qp.set_a(Y, 0, 1); qp.set_b(0, 4);
    qp.set_a(X, 1, 4); qp.set_a(Y, 1, 2); qp.set_b(1, a*b);
    qp.set_a(X, 2, -1); qp.set_a(Y, 2, 1); qp.set_b(2, 1);
    qp.set_c(Y, -b);
    qp.set_d(X, X, 2*a);

    Solution s = CGAL::solve_quadratic_program(qp, ET());
    assert (s.solves_quadratic_program(qp));

    if (s.is_infeasible()) {
        cout << "no" << endl;
    } else if (s.is_unbounded()) {
        cout << "unbounded" << endl;
    } else {
        assert (s.is_optimal());
        long result = floor(-CGAL::to_double(s.objective_value()));
        cout << result << endl;
    }
}

void solve_2(int a, int b){
    Program qp (CGAL::LARGER, false, 0, true, 0);
    const int X = 0;
    const int Y = 1;
    const int Z2 = 2;
    qp.set_a(X, 0, 1); qp.set_a(Y, 0, 1); qp.set_b(0, -4);
    qp.set_a(X, 1, 4); qp.set_a(Y, 1, 2); qp.set_a(Z2, 1, 1); qp.set_b(1, -a*b);
    qp.set_a(X, 2, -1); qp.set_a(Y, 2, 1); qp.set_b(2, -1);
    qp.set_u(Z2, false, 0);
    qp.set_d(X, X, 2*a);
    qp.set_c(Y, b);
    qp.set_d(Z2, Z2, 2*1);

    Solution s = CGAL::solve_quadratic_program(qp, ET());
    assert (s.solves_quadratic_program(qp));

    if (s.is_infeasible()) {
        cout << "no" << endl;
    } else if (s.is_unbounded()) {
        cout << "unbounded" << endl;
    } else if (s.is_optimal()){
        long result = ceil(CGAL::to_double(s.objective_value()));
        cout << result << endl;
    } else {
        cout << "no" << endl;
    }
}


int main() {
    int p; cin >> p;

    while (p > 0) {
        int a, b;
        cin >> a >> b;
        if (p == 1) solve_1(a, b);
        else if (p == 2) solve_2(a, b);
        cin >> p;
    }
}
