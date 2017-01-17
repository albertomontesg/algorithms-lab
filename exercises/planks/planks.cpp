#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

typedef vector<vector<int> > vecvec;

void back_track(vector<int>& planks, vecvec& assigment, vecvec& F, int id, int ubound) {
    if (id >= ubound) {
        vector<int> tuple(4, 0);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < assigment[i].size(); j++)
                tuple[i] += planks[assigment[i][j]];
        }
        F.push_back(tuple);
        return;
    }

    for (int side = 0; side < 4; side++) {
        assigment[side].push_back(id);
        back_track(planks, assigment, F, id+1, ubound);
        assigment[side].pop_back();
    }
}

void planks() {
    int n; cin >> n;

    vector<int> planks(n);
    int sum = 0;
    long long n_sol = 0;

    for (int i = 0; i < n; i++) { cin >> planks[i]; sum += planks[i]; }

    if (sum % 4 != 0) {
        cout << 0 << endl;
        return;
    }

    vecvec F1, F2, assigment1(4), assigment2(4);
    back_track(planks, assigment1, F1, 0, n/2);
    back_track(planks, assigment2, F2, n/2, n);
    sort(F2.begin(), F2.end());

    for (int idx = 0; idx < F1.size(); idx++) {
        vector<int> member = F1[idx];
        for (int i = 0; i < 4; i++)
            member[i] = sum/4 - member[i];

        pair<vecvec::iterator, vecvec::iterator> bounds;
        bounds = equal_range(F2.begin(), F2.end(), member);
        n_sol += distance(bounds.first, bounds.second);
    }

    cout << n_sol / 24 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        planks();
    }
}
