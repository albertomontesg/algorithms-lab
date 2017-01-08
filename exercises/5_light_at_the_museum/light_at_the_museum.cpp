#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int>      pair_int;


void light_at_the_museum() {
    int N, M; cin >> N >> M;

    vector<int> brightness(M);
    for (int i = 0; i < M; i++) cin >> brightness[i];

    vector<vector<int> > state_on(N, vector<int>(M)), state_off(N, vector<int>(M));
    for (int j = 0; j < N; j++)
        for (int i = 0; i < M; i++) cin >> state_on[j][i] >> state_off[j][i];


    // Try to reduce the runtime from (N*M*2^N) to (K*2^(N/2))
    // Approach of two subsets to obtain the same sum
    int N_1 = N / 2;
    int N_2 = N - N_1;
    vector<vector<int> > S_1(N_1, vector<int>(M, 0));
    vector<vector<int> > S_2(N_2, vector<int>(M, 0));
    vector<int> A_1(N_1);
    vector<int> A_2(N_2);

    // Create subset of sums for S1
    for (int k = 0; k < 1<<N_1; k++) {
        int count = 0;
        for (int i = 0; i < N_1; i++) {
            bool state_n = (k & 1<<i) != 0;
            if (state_n) count++;
            for (int j = 0; j < M; j++) {
                if (state_n) S_1[k][j] += state_off[i][j];
                else S_1[k][j] += state_on[i][j];
            }
        }
        A_1[k] = count;
    }
    // Create subset of sums for S1
    for (int k = 0; k < 1<<N_2; k++) {
        int count = 0;
        for (int i = 0; i < N_2; i++) {
            bool state_n = (k & 1<<i) != 0;
            if (state_n) count++;
            for (int j = 0; j < M; j++) {
                if (state_n) S_2[k][j] += state_off[N_1+i][j];
                else S_2[k][j] += state_on[N_1+i][j];
            }
        }
        A_2[k] = count;
    }


    //
    // bool result = false;
    // int min_switches = N;
    // for (int k = 0; k < 1<<N; k++) {
    //     vector<int> accum(brightness);
    //     int count = 0;
    //     for (int i = 0; i < N; i++) {
    //         bool state_m = (k & 1<<i) != 0;
    //         if (state_m) count++;
    //         for (int j = 0; j < M; j++) {
    //             if (state_m) {
    //                 accum[j] -= state_off[i][j];
    //             } else {
    //                 accum[j] -= state_on[i][j];
    //             }
    //         }
    //     }
    //     if (all_of(accum.begin(), accum.end(), [](int i){ return i == 0; })) {
    //         result = true;
    //         min_switches = min(min_switches, count);
    //     }
    // }
    //
    // if (result) cout << min_switches << endl;
    // else cout << "impossible\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        light_at_the_museum();
    }
}
