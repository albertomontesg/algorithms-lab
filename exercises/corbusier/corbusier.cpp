#include <vector>
#include <iostream>

using namespace std;

void corbusier() {
    int n, i, k;
    cin >> n >> i >> k;

    vector<int> disks(n);
	vector<vector<bool> > T(n, vector<bool>(k, false));

    for (int j = 0; j < n; j++) cin >> disks[j];

	int h;
	for (int d = 0; d < n; d++) {
		h = disks[d];

        T[d][h%k] = true;
		if (d > 0) {
			for (int j = 0; j < k; j++) {
				if (T[d-1][j]) {
                    T[d][j] = true;
					T[d][(j+h)%k] = true;
				}
			}
		}

		if (T[d][i]) {
			cout << "yes\n";
			return;
		}
	}
	cout << "no\n";
}


int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        corbusier();
    }
}
