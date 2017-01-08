#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


void light_at_the_museum() {
    int N, M; cin >> N >> M;

    vector<int> brightness(M);
    for (int i = 0; i < M; i++) cin >> brightness[i];

    vector<vector<int> > state_on(N, vector<int>(M)), state_off(N, vector<int>(M));
    for (int j = 0; j < N; j++)
        for (int i = 0; i < M; i++) cin >> state_on[j][i] >> state_off[j][i];

    bool result = false;
    int min_switches = N;
    for (int k = 0; k < 1<<N; k++) {
        vector<int> accum(brightness);
        int count = 0;
        for (int i = 0; i < N; i++) {
            bool state_m = (k & 1<<i) != 0;
            if (state_m) count++;
            for (int j = 0; j < M; j++) {
                if (state_m) {
                    accum[j] -= state_off[i][j];
                } else {
                    accum[j] -= state_on[i][j];
                }
            }
        }
        if (all_of(accum.begin(), accum.end(), [](int i){ return i == 0; })) {
            result = true;
            min_switches = min(min_switches, count);
        }
    }

    if (result) cout << min_switches << endl;
    else cout << "impossible\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        light_at_the_museum();
    }
}
