/*
Implementation sliding window.
Hint: to improve the efficiency, instead of loop along all the appearance vector to see if all the
words appear, keep up a counter and changing it with conditions. It is much more efficient and clean
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <limits.h>

using namespace std;

struct word {
    int id;
    int position;
};

void search_snippets() {
    int n; cin >> n;

    vector<int> m(n);
    int t = 0;              // total word appearance
    for (int i = 0; i < n; i++) {
        cin >> m[i];
        t += m[i];
    }

    vector<word > w; w.reserve(t);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m[i]; j++) {
            word wo; wo.id = i;
            cin >> wo.position;
            w.push_back(wo);
        }
    }
    sort(w.begin(), w.end(), [](word a, word b) {
        return a.position < b.position;
    });

    vector<int> a(n, 0);
    int min_d = w[t-1].position - w[0].position + 1;
    int s = 0, e = 0, u = n; // start, end, and uncovered counter
    a[w[s].id]++; u--;
    // Sliding Window
    while (e != t) {
        while (e < t - 1 && u > 0) {
            e++;
            if (a[w[e].id] == 0) u--;
            a[w[e].id]++;
        }
        if (u != 0) break;
        do {
            a[w[s].id]--;
            if (a[w[s].id] == 0) ++u;
        } while (++s != e && u==0);     // Even you go out of the while loop, s will have been
                                        // incresed undiredbly
        min_d = min(min_d, w[e].position - w[s-1].position + 1);
    }

    cout << min_d << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        search_snippets();
    }
}
