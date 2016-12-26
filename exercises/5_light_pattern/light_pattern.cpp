#include <vector>
#include <queue>
#include <iostream>

using namespace std;


void light_pattern() {
    int n, k, x, p, b, s, q;
    cin >> n >> k >> x;
    p = n / k;

    vector<unsigned short int> bulbs_state(p), pattern(p);
    for (int i = 0; i < p; i++) {
        s = 0; q = 0;   // s to store the bulb state, q to store the pattern
        for (int j = 0; j < k; j++) {
            cin >> b;
            if (b == 1) s |= 1 << j;
            if (j % 2 == 0) q |= (1 - (x & 1)) << j;
            else q |= (x & 1) << j;
        }
        bulbs_state[i] = s;
        pattern[i] = q;
        cout << q;
    }
    cout << endl;

    /*
    Go through the blocks from left to right. Is there a recursive relationship between the number of operations needed to get blocks 1..i to have the right patterns and the number of operations needed to get blocks 1..i-1 to have the right patterns. If so, you could do DP. If not, why not, and how could it be fixed? This should point you into the right direction.
    */


}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        light_pattern();
    }
}
