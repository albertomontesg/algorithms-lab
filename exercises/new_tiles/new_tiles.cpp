
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void new_tiles() {
    int h, w;
    cin >> h >> w;

	vector<uint32_t> floor_plan(h, 0);
	int p;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> p;
			if (p == 1) floor_plan[i] |= 0x01<<j;
		}
	}

	

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        new_tiles();
    }
}
