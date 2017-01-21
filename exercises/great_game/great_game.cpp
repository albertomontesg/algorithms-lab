#include <vector>
#include <iostream>
#include <climits>

using namespace std;


int max_(vector<vector<int> > &transitions, int start, int end,
    vector<int> &min_mem, vector<int> &max_mem);

int min_(vector<vector<int> > &transitions, int start, int end,
        vector<int> &min_mem, vector<int> &max_mem) {

    if (start == end) {
        min_mem[start] = 0;
        return 0;
    }

    int min_dist = INT_MAX;
    for (int v : transitions[start]) {
        if (max_mem[v] == -1) {
            max_(transitions, v, end, min_mem, max_mem);
        }
        min_dist = min(min_dist, max_mem[v]);
    }
    min_mem[start] = min_dist + 1;
    return min_mem[start];
}


int max_(vector<vector<int> > &transitions, int start, int end,
    vector<int> &min_mem, vector<int> &max_mem) {

    if (start == end) {
        max_mem[start] = 0;
        return 0;
    }

    int max_dist = 0;
    for (int v : transitions[start]) {
        if (min_mem[v] == -1) {
            min_(transitions, v, end, min_mem, max_mem);
        }
        max_dist = max(max_dist, min_mem[v]);
    }
    max_mem[start] = max_dist + 1;
    return max_mem[start];
}

void great_game() {
    int n, m;
    cin >> n >> m;
    int r, b;
    cin >> r >> b;
    // set to 0-index
    r--; b--;

    vector<vector<int> > transitions(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // set to 0-index
        u--; v--;
        transitions[u].push_back(v);
    }

    // Create memory vectors
    vector<int> min_mem(n, -1), max_mem(n, -1);

    // For each of the starting possitions, check which one has minimum movements to win the game.
    int red_moves = min_(transitions, r, n-1, min_mem, max_mem);
    int black_moves = min_(transitions, b, n-1, min_mem, max_mem);

    cout << (black_moves < red_moves || (black_moves == red_moves && black_moves % 2 == 0)) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        great_game();
    }
}
