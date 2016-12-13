
#include <iostream>
#include <map>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
// Namespaces
using namespace std;
using namespace boost;


// BGL Graph definitions
typedef adjacency_list<vecS, vecS, undirectedS> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;


void add_connection(Graph& G, vector<vector<bool> >& chessboard, int n, int i, int j, int new_i, int new_j) {
    if (new_i >= n || new_i < 0) return;
    if (new_j >= n || new_j < 0) return;
    if ( !chessboard[new_i][new_j] ) return;

    add_edge(i*n + j, new_i*n + new_j, G);
    return;
}


void placing_knights() {
    int n; cin >> n;
    vector<vector<bool> > chessboard(n, vector<bool>(n));

    // Read chessboardx
    int c = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool p; cin >> p;
            chessboard[i][j] = p;
            if ( p ) c++;
        }
    }

    Graph G(n*n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (chessboard[i][j]) {
                add_connection(G, chessboard, n, i, j, i-1, j-2);
                add_connection(G, chessboard, n, i, j, i-1, j+2);
                add_connection(G, chessboard, n, i, j, i+1, j-2);
                add_connection(G, chessboard, n, i, j, i+1, j+2);
                add_connection(G, chessboard, n, i, j, i-2, j-1);
                add_connection(G, chessboard, n, i, j, i-2, j+1);
                add_connection(G, chessboard, n, i, j, i+2, j-1);
                add_connection(G, chessboard, n, i, j, i+2, j+1);
            }
        }
    }

    vector<Vertex> mate(n*n);
    checked_edmonds_maximum_cardinality_matching(G, &mate[0]);
    int matches = matching_size(G, &mate[0]);

    cout << c - matches << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        placing_knights();
    }
}
