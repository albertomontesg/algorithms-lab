/*
Implementation that first find the first interval that contains all the words. Then slide this
interval along the words and try to reduce if possible to find the minimum.
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>


using namespace std;


bool not_at_end(vector<vector<long> >& queues, vector<vector<long>::iterator>& its) {
    for (int i = 0; i < queues.size(); i++) {
        if (its[i] == queues[i].end()) { return false; }
    }
    return true;
}

void search_snippets() {
    int n; cin >> n;

    vector<long> wo(n);
    vector<vector<long> > wq(n);

    // Store the word appearance
    for (int i = 0; i < n; i++) {
        cin >> wo[i];
        wq[i] = vector<long>(wo[i]);
    }

    // Store in respective queues the word position
    for (long i = 0; i < n; i++) {
        for (int j = 0; j < wo[i]; j++) {
            cin >> wq[i][j];
        }
    }

    long l_w = distance(wo.begin(), max_element(wo.begin(), wo.end()));
    long min_distance = LONG_MAX;

    for (int i = 0; i < wo[l_w]; i++) {
        long v = wq[l_w][i];
        long min_upper = LONG_MAX, max_lower = 0;

        for (int j = 0; j < n; j++) {
            if (j == l_w) continue;
            auto min_p = upper_bound(wq[j].begin(), wq[j].end(), v);
            if (min_p != wq[j].end()) min_upper = min(min_upper, *min_p);
            auto max_p = upper_bound(wq[j].begin(), wq[j].end(), v, greater<long>());
            if (max_p != wq[j].end()) max_lower = min(max_lower, *max_p);
        }

        if ( min_upper == LONG_MAX ) min_upper = v;
        if ( max_lower == 0) max_lower = v;

        long d = min_upper - max_lower + 1;
        min_distance = min(min_distance, d);
    }

    cout << min_distance << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        search_snippets();
    }
}
