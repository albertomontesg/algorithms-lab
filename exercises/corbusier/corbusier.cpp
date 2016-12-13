#include <vector>
#include <iostream>

using namespace std;


void corbusier() {
    int n, i, k;
    cin >> n >> i >> k;

    vector<long> disk(n);
    for (int j = 0; j < n; j++) cin >> disk[j];

    bool solution = false;
    for (int j = 1; j < 1<<n; j++) {
        long count = 0;
        for (int p = 0; p < n; p++) {
            if (j & (1<<p)) {
                count += disk[p];
            }
        }
        if (count % k == i) {
            solution = true;
            break;
        }
    }

    if (solution) cout << "yes" << endl;
    else cout << "no" << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        corbusier();
    }
}
