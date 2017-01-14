#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

typedef pair<int, int>                      pair_int;
typedef vector<vector<int> >                vecvec;
typedef vector<pair<vector<int>,int> >      vecpairvec;


void create_subset(vecvec& state_on, vecvec& state_off, vecpairvec& F, int dbound, int ubound) {
    int N = ubound - dbound;
    int M = state_on[0].size();
    for (int k = 0; k < 1<<N; k++) {
        vector<int> tuple(M, 0);
        int count = 0;

        for (int i = 0; i < N; i++) {
            bool changed_state = (k & 1<<i) != 0;
            if (changed_state) count++;

            for (int j = 0; j < M; j++)
                tuple[j] += (changed_state) ? state_off[i+dbound][j] : state_on[i+dbound][j];
        }
        F.push_back(make_pair(tuple, count));
    }
}

struct Comp {
    bool operator() (pair<vector<int>, int> P, vector<int> V) {
        return P.first < V;
    }
    bool operator() (vector<int> V, pair<vector<int>, int> P) {
        return V < P.first;
    }
};

void light_at_the_museum() {
    int N, M; cin >> N >> M;

    vector<int> brightness(M);
    for (int i = 0; i < M; i++) cin >> brightness[i];

    vector<vector<int> > state_on(N, vector<int>(M)), state_off(N, vector<int>(M));
    for (int j = 0; j < N; j++)
        for (int i = 0; i < M; i++) cin >> state_on[j][i] >> state_off[j][i];


    // Create all combinations for two subsets (divide and list)
    vecpairvec F1, F2;
    create_subset(state_on, state_off, F1, 0, N/2);
    create_subset(state_on, state_off, F2, N/2, N);
    sort(F2.begin(), F2.end());

    int min_changes = INT_MAX;
    for (int idx = 0; idx < F1.size(); idx++) {
        vector<int> missing = F1[idx].first;
        for (int i = 0; i < M; i++) {
            missing[i] = brightness[i] - missing[i];
        }

        pair<vecpairvec::iterator, vecpairvec::iterator>  it_pair;
        it_pair = equal_range(F2.begin(), F2.end(), missing, Comp());

        for (auto it = it_pair.first; it != it_pair.second; it++) {
            int count = it->second + F1[idx].second;
            min_changes = min(min_changes, count);
        }
    }

    if (min_changes == INT_MAX) cout << "impossible\n";
    else cout << min_changes << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        light_at_the_museum();
    }
}
