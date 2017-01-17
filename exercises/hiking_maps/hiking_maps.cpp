#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <vector>
#include <algorithm>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                                          P;
typedef std::vector<P>                                      Pts;
typedef std::vector<int>                                    Covered;
typedef std::vector<Covered>                                Trs;
typedef Covered::const_iterator                             Iterator;

using namespace std;

// Function to check whether a point is inside a triangle
inline bool contains(const Pts& t, const P& p) {
    return !CGAL::right_turn(t[0],t[1],p) && !CGAL::right_turn(t[2],t[3],p) && !CGAL::right_turn(t[4],t[5],p);
}


void hiking_maps() {
    int m, n; cin >> m >> n;

    // Read the path
    Pts path(m);
    long x, y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        path[i] = P(x, y);
    }

    // Read the triangles
    Trs triangles(n);
    for (int i = 0; i < n; ++i) {
        Pts t;
        for (std::size_t j = 0; j < 6; ++j) {
            P p;
            std::cin >> p;
            t.push_back(p);
        }
        // Ensure correct order for orientation tests
        for (int j = 0; j < 6; j+=2)
            if (CGAL::right_turn(t[j],t[j+1],t[(j+2)%6])) std::swap(t[j],t[j+1]);
        // Store which path segments are covered
        bool prev = contains(t,path[0]);
        for (int j = 1; j < m; ++j) {
            if (contains(t,path[j])) {
                if (prev) triangles[i].push_back(j-1);
                else prev = true;
            } else
                prev = false;
        }
    }

    // search for the cover by scanning through the sequence of triangles
    Covered covered(m-1,0); // #times i,i+1 is covered
    int uncovered = m-1; // #uncovered segments (covered[i]==0)
    int best = n; // size of best range so far
    for (int tb = 0, te = 0; tb != n;) {
        // Ensure covering
        for (; uncovered > 0 && te != n; te++) {
            for (Iterator j = triangles[te].begin(); j != triangles[te].end(); j++)
                if (++covered[*j] == 1) --uncovered;
        }
        if (uncovered != 0) break;
        // Can we remove tb?
        do {
            for (Iterator j = triangles[tb].begin(); j != triangles[tb].end(); j++)
                if (--covered[*j] == 0) uncovered++;
        } while (++tb != te && uncovered == 0);
        best = min(best, te - tb + 1);
    }
    cout << best << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        hiking_maps();
    }
}
