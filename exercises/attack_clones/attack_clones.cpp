
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;


void compute_jedis() {
    long N, M; cin >> N >> M;

    vector<pair<int, int> > jedis(N);
    // vector<pair<int,int> > nn_jedis, sum_jedis;
    map<int, int> nn_jedis;
    map<int, int> sum_jedis;

    int a, b;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        a--; b--;                                       // Re-index to 0-based index
        jedis[i] = make_pair(a, b);
        nn_jedis[a]++;
        if (b < a) nn_jedis[0]++;
        if (b < M - 1) nn_jedis[b+1]--;
    }

    // Find the position which no interval overlaps, or the one that less intervals overlap (at
    // most 10 by statement)
    int prev_sum = 0;
    int min_jedis = INT_MAX, min_jedis_pos = -1;
    for (auto nn_jedi : nn_jedis) {
        int pos = nn_jedi.first;
        sum_jedis[pos] = prev_sum + nn_jedi.second;
        prev_sum += nn_jedi.second;
        // cout << pos << "\t" << prev_sum << endl;
        if (prev_sum < min_jedis) {
            min_jedis = prev_sum;
            min_jedis_pos = pos;
        }
    }

    // Separate the intervals between the ones that cut k_0 and the ones that not.
    vector<pair<int,int> > jedis_cutting, jedis_not_cutting;
    int ai, bi;
    int k0 = min_jedis_pos;
    for (int i = 0; i < N; i++) {
        a = jedis[i].first;
        b = jedis[i].second;
        ai = (a - k0 + M) % M;
        bi = (b - k0 + M) % M;

        if (bi < ai) jedis_cutting.push_back(make_pair(bi, ai));
        else jedis_not_cutting.push_back(make_pair(bi, ai));
    }

    // Sort by ending interval position
    sort(jedis_not_cutting.begin(), jedis_not_cutting.end());

    // Interval Scheduling for the non-cutting-min position intervals
    int result = 0, lastb = -1;
    for (int i = 0; i < jedis_not_cutting.size(); i++) {
        if (jedis_not_cutting[i].second > lastb) {
            result++;
            lastb = jedis_not_cutting[i].first;
        }
    }

    // Now the same algorithm of Interval Scheduling but for each of the interval that cut the min
    // jedis position
    int result_cutting;
    for (int j = 0; j < jedis_cutting.size(); j++) {
        result_cutting = 1;
        lastb = jedis_cutting[j].first;
        for (int i = 0; i < jedis_not_cutting.size(); i++) {
            if (jedis_not_cutting[i].second > lastb && jedis_not_cutting[i].first < jedis_cutting[j].second) {
                result_cutting++;
                lastb = jedis_not_cutting[i].first;
            }
        }
        result = max(result, result_cutting);
    }

    cout << result << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for (int i = 0; i < t; i++) {
        compute_jedis();
    }
    return 0;
}
