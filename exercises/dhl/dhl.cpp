#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

using namespace std;


int dp(vector<vector<int> >& sum, int pos_a, int pos_b, vector<vector<int> >& memory) {

    // Check memory first
    if (memory[pos_a][pos_b] != -1) return memory[pos_a][pos_b];

    // Look for the best combination to reduce the cost given an specific position of the two stacks
    int pick_a, pick_b, new_cost, cost = INT_MAX;

    // Separate the iteration, first look at the first stack and take the first volume
    pick_a = sum[0][pos_a] - sum[0][pos_a-1];
    for(int i = pos_b - 1; i >= 0; i--) {
        if ((pos_a-1 == 0 && i > 0) || (pos_a-1 > 0 && i == 0)) continue;
        pick_b = sum[1][pos_b] - sum[1][i];

        new_cost = (memory[pos_a-1][i] != -1) ? memory[pos_a-1][i] : dp(sum, pos_a-1, i, memory);
        cost = min(cost, new_cost + pick_a*pick_b);
    }

    pick_b = sum[1][pos_b] - sum[1][pos_b-1];
    for(int i = pos_a - 1; i >= 0; i--) {
        if ((i == 0 && pos_b-1 > 0) || (i > 0 && pos_b-1 == 0)) continue;
        pick_a = sum[0][pos_a] - sum[0][i];

        new_cost = (memory[i][pos_b-1] != -1) ? memory[i][pos_b-1] : dp(sum, i, pos_b-1, memory);
        cost = min(cost, new_cost + pick_a*pick_b);
    }

    memory[pos_a][pos_b] = cost;
    return cost;

}

void dhl() {
    int n; cin >> n;

    vector<vector<int> > sum(2, vector<int>(n+1));
    sum[0][0] = 0; sum[1][0] = 0;

    int v;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> v; v--;
            sum[i][j+1] = sum[i][j] + v;
        }
    }

    int pos_a = n, pos_b = n;

    // Build memory matrix
    vector<vector<int> > memory(n+1, vector<int>(n+1, -1));
    memory[0][0] = 0;

    int cost = dp(sum, pos_a, pos_b, memory);
    cout << cost << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        dhl();
    }
}
