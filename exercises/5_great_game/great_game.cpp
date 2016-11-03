#include <vector>
#include <iostream>

using namespace std;


int play(int r, int b, int n_play, int n, vector<vector<int> >& transitions, vector<vector<int> >& mem) {
    /*  plays =
        turn % 2 == 0  -> Sherlock's
        turn % 2 == 1 -> Moriarty */
    int plays = n_play % 2;
    int turn = (n_play % 2 == 1) ? (n_play - 1) / 2 : n_play / 2;

    // Breaking case
    if (r == n-1) return 0; // Sherlock has win
    else if (b == n-1) return 1; // Moriarty has win

    

    if (plays == 0) {
        // Holmes strategy
        int meeple = (turn % 2 == 0) ? r : b;

        int wining_strategy = 1;
        for (int j = 0; j < transitions[meeple].size(); j++) {
            int next_pos = transitions[meeple][j];
            int w;
            if (turn % 2 == 0) {
                w = play(next_pos, b, n_play+1, n, transitions, mem);
            } else {
                w = play(r, next_pos, n_play+1, n, transitions, mem);
            }
            wining_strategy &= w;
        }

    } else {
        // Moriarty strategy
        int meeple = (turn % 2 == 0) ? b : r;

        int wining_strategy = 0;
        for (int j = 0; j < transitions[meeple].size(); j++) {
            int next_pos = transitions[meeple][j];
            int w;
            if (turn % 2 == 0) {
                w = play(r, next_pos, n_play+1, n, transitions, mem);
            } else {
                w = play(next_pos, b, n_play+1, n, transitions, mem);
            }
            wining_strategy |= w;
        }
    }


    int h_meeple = (turn % 2 == 0) ? r : b;
    int m_meeple = (turn % 2 == 0) ? b : r;

    if (mem[turn%2][h_meeple] != -1) {
        return mem[turn%2][h_meeple];
    }



    // starting with

}


void great_game() {
    int n, m;
    cin >> n >> m;
    int r, b;
    cin >> r >> b;
    // set to 0-index
    r--; b--;

    vector<vector<int> > transitions(n, vector<int>(0));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // set to 0-index
        u--; v--;
        transitions[u].push_back(v);
    }

    // Create memory vector
    vector<vector<vector<int> > > mem(2, vector<vector<int> >(2, vector<int>(n, -1)));




}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        great_game();
    }
}
