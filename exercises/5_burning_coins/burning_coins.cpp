#include <vector>
#include <iostream>

using namespace std;

void burning_coins() {
    int n; cin >> n;

    int odd = 0, even = 0;
    for (int i = 0; i < n; i++) {
        int v; cin >> v;
        if (i % 2 == 0) {
            even += v;
        } else {
            odd += v;
        }
    }

    cout << min(even, odd) << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        burning_coins();
    }
}
