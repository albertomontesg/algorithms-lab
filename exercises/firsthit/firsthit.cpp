#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <stdexcept>
#include <limits>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel       K;
typedef result_of<K::Intersect_2(K::Ray_2,K::Segment_2)>::type  IT;

// round down to next double
double floor_to_double(const K::FT& x) {
    double a = floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

// read segment cin; as each coordinate can be represented as a
// long, this is significantly faster than K::Segment_2 s; cin >> s;
inline K::Segment_2 read_segment() {
    long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    return K::Segment_2(K::Point_2(x1,y1), K::Point_2(x2,y2));
}

// clip/set target of s to o
void shorten_segment(K::Segment_2& s, const IT& o) {
    if (const K::Point_2* p = boost::get<K::Point_2>(&*o))
        s = K::Segment_2(s.source(), *p);
    else if (const K::Segment_2* t = boost::get<K::Segment_2>(&*o))
        // select endpoint of *t closer to s.source()
        if (CGAL::collinear_are_ordered_along_line (s.source(), t->source(), t->target()))
            s = K::Segment_2(s.source(), t->source());
        else
            s = K::Segment_2(s.source(), t->target());
    else
        throw runtime_error("Strange segment intersection.");
}

void find_hit(size_t n) {
    // read input
    K::Ray_2 r;
    cin >> r;
    vector<K::Segment_2> segs;
    segs.reserve(n);
    for (size_t i = 0; i < n; ++i) segs.push_back(read_segment());
    random_shuffle(segs.begin(), segs.end());

    // clip the ray at each segment hit (cuts down on the number of
    // intersection points to be constructed: for a uniformly random
    // order of segments, the expected number of constructions is
    // logarithmic in the number of segments that intersect the initial // ray.)
    K::Segment_2 rc(r.source(), r.source());

    // find some segment hit by r
    for (size_t i; i < n; ++i)
        if (CGAL::do_intersect(segs[i], r)) {
            shorten_segment(rc, CGAL::intersection(segs[i], r));
            break;
        }

    if (i == n) { cout << "no\n"; return; }
    // check remaining segments against rc
    while (++i < n)
        if (CGAL::do_intersect(segs[i], rc))
            shorten_segment(rc, CGAL::intersection(segs[i], r)); // not rc!

    cout << floor_to_double(rc.target().x()) << " " << floor_to_double(rc.target().y()) << "\n";

}

int main() {
    // sanity check
    if (numeric_limits<long>::digits < 51)
        throw runtime_error("long has <51 bits mantissa");
    ios_base::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(0);
    for (size_t n; cin >> n && n > 0;)
        find_hit(n);
    return 0;
}