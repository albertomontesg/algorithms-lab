#include <vector>
#include <iostream>

using namespace std;

void test_false_coin() {
    int n; cin >> n;

    vector<int> candidates(n, 0);
    vector<int> lw_coins(n, 0), hw_coins(n, 0);

    int num_trials; cin >> num_trials;

    for (int i = 0; i < num_trials; i++) {
        int num_per_side; cin >> num_per_side;

        vector<int> left_coins(n, false), right_coins(n, false);
        int left_pos, right_pos;
        for (int j = 0; j < num_per_side; j++) {
            cin >> left_pos;
            left_coins[left_pos-1] = true;
        }
        for (int j = 0; j < num_per_side; j++) {
            cin >> right_pos;
            right_coins[right_pos-1] = true;
        }

        char comparison; cin >> comparison;

        for (int j = 0; j < n; j++) {
            switch (comparison) {
                case '=': {
                    if (left_coins[j] || right_coins[j])
                        candidates[j] = -1;
                    else if (candidates[j] == 0)
                        candidates[j] = 1;
                    break;
                }
                case '<': {
                    if (left_coins[j]) {
                        lw_coins[j]++;
                        if (hw_coins[j] > 0) {
                            candidates[j] = -1;
                        } else if (candidates[j] == 0) {
                            candidates[j] = 1;
                        }
                    } else if (right_coins[j]) {
                        hw_coins[j]++;
                        if (lw_coins[j] > 0) {
                            candidates[j] = -1;
                        } else if (candidates[j] == 0) {
                            candidates[j] = 1;
                        }
                    } else {
                        candidates[j] = -1;
                    }
                    break;
                }
                case '>': {
                    if (right_coins[j]) {
                        lw_coins[j]++;
                        if (hw_coins[j] > 0) {
                            candidates[j] = -1;
                        } else if (candidates[j] == 0) {
                            candidates[j] = 1;
                        }
                    } else if (left_coins[j]) {
                        hw_coins[j]++;
                        if (lw_coins[j] > 0) {
                            candidates[j] = -1;
                        } else if (candidates[j] == 0) {
                            candidates[j] = 1;
                        }
                    } else {
                        candidates[j] = -1;
                    }
                    break;
                }
                default: break;
            }
        }
    }

    int count_candidates = 0;
    int coin_id = 0;
    for (int i = 0; i < n; i++) {
        if (candidates[i] == 1) {
            count_candidates++;
            coin_id = i + 1;
        }
    }
    if (count_candidates > 1) {
        coin_id = 0;
    }
    cout << coin_id << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        test_false_coin();
    }
}
