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

    vector<vector<long>::iterator> it(n);
    for (int i = 0; i < n; i++) { it[i] = wq[i].begin(); }

    long min_distance = LONG_MAX;
    while ( not_at_end(wq, it) ) {
        struct {
            bool operator()(vector<long>::iterator a, vector<long>::iterator b) {
                return *a < *b;
            }
        } Cmp;
        auto min_p = distance(it.begin(), min_element(it.begin(), it.end(), Cmp));
        auto max_p = distance(it.begin(), max_element(it.begin(), it.end(), Cmp));
        long d = *(it[max_p]) - *(it[min_p]) + 1;
        min_distance = min(d, min_distance);
        it[min_p]++;
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
