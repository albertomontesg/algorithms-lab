
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct center {
	center (int n) {
		sup = vector<uint16_t>(n, 0);
	}
	vector<uint16_t> sup;
	map<uint16_t, map<int, int> > extsup;
	map<int, int> bestmap;
};


int best_stormtroopers(vector<center>& centers, int c, int mask, const int S) {
	auto bestit = centers[c].bestmap.find(mask);
	if (bestit != centers[c].bestmap.end())
		return bestit->second;

	int best = 0;
	for (int k = 0; k < (0x1<<S); k++) {
		// Mask refers to the stormtroopers that can not be choosen because are being supervised
		if ((k & mask) != 0) continue;

		bool valid = true;
		// Check the validity looking if any of the stormtroopers supervise each other in this
		// configurations
		for (int i = 0; i < S && valid; i++) {
			if (((k & (0x1<<i)) != 0) && ((k & centers[c].sup[i]) != 0)) valid = false;
		}
		if (!valid) continue;

		int count = 0;
		// Count the strompers being sabotaged
		for (int i = 0; i < S; i++) {
			if (k & (0x1<<i)) count++;
		}
		// Now compute the mask (the stormtroopers that on the children centers are being
		// supervised by this configuration) and with DP count the maximum number of stormtroopers
		// that are not being supervised by each other.
		for (auto& esup : centers[c].extsup) {
			int nmask = 0;
			for (auto& p : esup.second) {
				if (k & 0x1<<p.first) nmask |= p.second;
			}
			count += best_stormtroopers(centers, esup.first, nmask, S);
		}
		best = max(best, count);
	}
	centers[c].bestmap[mask] = best;
	return best;
}

void a_new_hope() {
	int K, S, M;
    cin >> K >> S >> M;

	vector<center> centers(K, center(S));

	int u, v, h, x, y;
	for (int i = 0; i < M; i++) {
		cin >> u >> v >> h;
		if (u == v) {
			for (int j = 0; j < h; j++) {
				cin >> x >> y;
				centers[u].sup[x] |= 0x1 << y;
			}
		}
		else {
			map<int, int> esup;
			for (int j = 0; j < h; j++) {
				cin >> x >> y;
				esup[x] |= 0x1 << y;
			}
			centers[u].extsup[v] = esup;
		}

	}

	cout << best_stormtroopers(centers, 0, 0, S) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        a_new_hope();
    }
}
