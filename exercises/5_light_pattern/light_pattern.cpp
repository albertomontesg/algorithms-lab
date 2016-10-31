#include <vector>
#include <iostream>

using namespace std;





void light_pattern() {
    int n, k, x;
    cin >> n >> k >> x;

    vector<bool> bulbs_state(n);
    for (int i = 0; i < n; i++) {
        int b; cin >> b;
        bulbs_state[i] = (b == 1) ? true: false;
    }



}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        light_pattern();
    }
}
