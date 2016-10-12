#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;



void moving_books() {
    long n; cin >> n;
    long m; cin >> m;

    vector<long> s(n), w(m);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> w[i];
    }

    // Check if the heviest box can not be bringed by nobody
    int max_s = *max_element(s.begin(), s.end());
    int max_w = *max_element(w.begin(), w.end());
    if (max_w > max_s) {
        cout << "impossible\n";
        return;
    }


    multiset<int, greater<int> > ws;
    sort(s.begin(), s.end(), greater<int>());

    for (int i = 0; i < m; i++) ws.insert(w[i]);
    int r = 0;
    while (!ws.empty()) {
        r++;
        for (int i = 0; i < n; i++) {
            auto j = ws.lower_bound(s[i]);
            if (j != ws.end()) {
                ws.erase(j);
            } else {
                break;
            }
        }
    }

    cout << 3*r-1 << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        moving_books();
    }
}
