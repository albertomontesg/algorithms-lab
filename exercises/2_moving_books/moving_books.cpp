#include <vector>
#include <iostream>

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


}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        moving_books();
    }
}
