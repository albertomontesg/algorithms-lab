#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

using namespace std;

double award(double k) {
    if (k > 1) {
        return exp2(k-2);
    } else if (k == 1) {
        return 1;
    } else {
        throw runtime_error("k can not be less than 1.");
    }
}

double play(vector<vector<int> >& stacks, vector<int> sp) {
    if (all_of(sp.begin(), sp.end(), [](int i){return i == 0;})) {
        return 0;
    }
    map<int, vector<bool> > groups;
    for (int i = 0; i < sp.size(); i++) {
        if (sp[i] == 0) {
            continue;
        }
        int c = stacks[i][sp[i]];
        if (groups.count(c) == 0) {
            groups[c] = vector<bool>(false);
            groups[c][i] = true;
        }
    }
    // Check for each group of colors, the award and recurisivity
    vector<double> results(0);
    int c = 0;
    for (auto it = groups.begin(); it != groups.end(); it++) {
        vector<bool> chips = it->second;
        double result = award(chips.size());
        vector<int> positions(sp.size());
        for (int j = 0; j < sp.size(); j++) {
            positions[j] = (chips[j]) ? sp[j] - 1 : sp[j];
        }
        result += play(stacks, positions);
        results[c++] = result;
    }
    return *max_element(results.begin(), results.end());
}


void poker_chips() {
    int n; cin >> n;

    vector<int> nb_chips(n);
    vector<vector<int> > stacks(n, vector<int>(0));
    vector<int> game_positions(n);

    for (int i = 0; i < n; i++) {
        cin >> nb_chips[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < nb_chips[i]; j++) {
            int c; cin >> c;
            stacks[i].push_back(c);
        }
        game_positions[i] = nb_chips[i] - 1;
    }

    double max_result = play(stacks, game_positions);
    cout << max_result << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        poker_chips();
    }
}
