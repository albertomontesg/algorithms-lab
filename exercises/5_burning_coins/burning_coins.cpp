#include <vector>
#include <iostream>

using namespace std;


int play(vector<int>& coins_values, int left_idx, int right_idx, bool turn, vector<vector<int> >& mem) {
    /*  turn = true  -> Your turn
        turn = false -> Friend's turn */

    // Final case if no coins left
    if (left_idx == right_idx) {
        return 0;
    }

    if (mem[left_idx][right_idx-1] > -1) {
        return mem[left_idx][right_idx-1];
    }

    // First take the left coins then the right one
    int left_result, right_result, result;
    if (turn) {
        left_result = coins_values[left_idx];
        left_result += play(coins_values, left_idx+1, right_idx, false, mem);
        right_result = coins_values[right_idx-1];
        right_result += play(coins_values, left_idx, right_idx-1, false, mem);
        result = (left_result > right_result) ? left_result : right_result;
        mem[left_idx][right_idx-1] = result;
        return result;
    } else {
        left_result = play(coins_values, left_idx+1, right_idx, true, mem);
        right_result = play(coins_values, left_idx, right_idx-1, true, mem);
        result = (left_result < right_result) ? left_result: right_result;
        mem[left_idx][right_idx-1] = result;
        return result;
    }
}


void burning_coins() {
    int n; cin >> n;

    vector<int> coins_values(n);
    for (int i = 0; i < n; i++) {
        cin >> coins_values[i];
    }

    // Add some memory storing the result for every pair of left and right indexes possible (speedup)
    vector<vector<int> > mem(n, vector<int>(n, -1));
    cout << play(coins_values, 0, n, true, mem) << endl;


}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        burning_coins();
    }
}
