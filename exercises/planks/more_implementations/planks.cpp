/*
Solution using backtracking with a running time of O(n 4^n) which is only good for the first testset
*/
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int back_track(vector<int>& planks, vector<vector<int> >& assigment, int id, const int side_length) {
    if (id >= planks.size()) {
        bool ok = true;
        for (int i = 0; i < 4; i++) {
            int sum = 0;
            for (int j = 0; j < assigment[i].size(); j++)
                sum += planks[assigment[i][j]];

            if (sum != side_length) {
                ok = false;
                break;
            }
        }
        if (ok) return 1;
        else return 0;
    }
    int counter = 0;
    for (int side = 0; side < 4; side++) {
        assigment[side].push_back(id);
        counter += back_track(planks, assigment, id+1, side_length);
        assigment[side].pop_back();
    }
    return counter;
}

void planks() {
    int n; cin >> n;

    vector<int> planks(n);
    int sum = 0;

    for (int i = 0; i < n; i++) { cin >> planks[i]; sum += planks[i]; }

    if (sum % 4 != 0) {
        cout << 0 << endl;
        return;
    }

    int side_length = sum / 4;
    vector<vector<int> > assigment(4);

    cout << back_track(planks, assigment, 0, side_length) / 24 << endl;


}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        planks();
    }
}
