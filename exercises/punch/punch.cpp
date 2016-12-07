#include <iostream>
#include <cassert>
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

void punch(){
    int n, k; cin >> n >> k;

    Program qp (CGAL::EQUAL, true, 0, false, 0);
    int c, v;
    for (int i = 0; i < n; i++) {
        cin >> c >> v;
        qp.set_c(i, c);
        qp.set_a(i, 0, v);
        // qp.set_d(i, i, 1);
    }
    qp.set_b(0, k);

    Solution s = CGAL::solve_linear_program(qp, ET());
    assert(s.solves_linear_program(qp));
    assert(s.is_optimal());

    // CGAL::Quadratic_program_solution<ET>::Variable_value_iterator opt = s.variable_values_begin();
    // int value = 0;
    // for (; opt != s.variable_values_end(); opt++) {
    //     int tmp = int(CGAL::to_double(*(opt)));
    //     if (tmp > 0) value++;
    // }
    // cout << value << endl;
    cout << CGAL::to_double(s.objective_value()) << endl;

}


int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;

    for (int i = 0; i < T; i++) {
        punch();
    }
}
