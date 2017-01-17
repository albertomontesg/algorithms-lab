#include <vector>
#include <map>
#include <stack>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

using namespace std;

// CGAL typedefs
typedef CGAL::Exact_predicates_inexact_constructions_kernel         K;
typedef pair<int, bool>                                             info_t;
typedef CGAL::Triangulation_vertex_base_with_info_2<info_t, K>      Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>                    Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                      Triangulation;
typedef Triangulation::Finite_faces_iterator                        FaceIt;
typedef Triangulation::Edge_iterator                                EdgeIt;
typedef Triangulation::Face_handle                                  FaceH;
typedef Triangulation::Vertex_handle                                VertexH;
typedef Triangulation::Vertex_circulator                            VertexCirculator;
typedef K::Point_2                                                  Point;
typedef K::Segment_2                                                Segment;
typedef K::Triangle_2                                               Triangle;


bool has_interference(Triangulation const & trg, K::FT const & rr) {
    for (auto e = trg.finite_edges_begin(); e != trg.finite_edges_end(); e++)
        if (trg.segment(*e).squared_length() <= rr) return true;
    return false;
}

bool try_two_colors(Triangulation & trg, K::FT const & rr) {
    for (auto v = trg.finite_vertices_begin(); v != trg.finite_vertices_end(); v++)
        v->info() = { 0, false };

    int components = 0;
    Triangulation trg0, trg1;
    for (auto v = trg.finite_vertices_begin(); v != trg.finite_vertices_end(); v++) {
        if (v->info().first == 0) {
            v->info().first = ++components;
            vector<VertexH> stack(1, v);
            do {
                VertexH h = stack.back();
                stack.pop_back();
                VertexCirculator c = trg.incident_vertices(h);
                do if (!trg.is_infinite(c) && CGAL::squared_distance(h->point(), c->point()) <= rr) {
                    if (c->info() == h->info()) return false;
                    if (c->info().first == 0) {
                        stack.push_back(c);
                        c->info() = { components, !h->info().second };
                    }
                } while (++c != trg.incident_vertices(h));
            } while (!stack.empty());
        }

        if (v->info().second) trg1.insert(v->point());
        else trg0.insert(v->point());
    }

    return !has_interference(trg0, rr) && !has_interference(trg1, rr);
}

void clues() {
    int n, m;
    long r;
    cin >> n >> m >> r;
    K::FT rr(r*r);

    vector<Point> stations(n);
    for (int i = 0; i < n; i++) cin >> stations[i];

    Triangulation trg;
    trg.insert(stations.begin(), stations.end());
    bool success = try_two_colors(trg, rr);

    for (int i = 0; i < m; i++) {
        Point holmes, watson;
        cin >> holmes >> watson;

        if (success) {
            if (CGAL::squared_distance(holmes, watson) <= rr) {
                cout << "y"; continue;
            }

            auto holmes_station = trg.nearest_vertex(holmes);
            auto watson_station = trg.nearest_vertex(watson);
            if (holmes_station->info().first == watson_station->info().first &&
                CGAL::squared_distance(holmes_station->point(), holmes) <= rr &&
                CGAL::squared_distance(watson_station->point(), watson) <= rr)
            {
                cout << "y"; continue;
            }
        }
        cout << "n";
    }
    cout << endl;

}


int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        clues();
    }
}
