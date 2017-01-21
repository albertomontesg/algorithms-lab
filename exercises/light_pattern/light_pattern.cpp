#include <vector>
 #include <iostream>

using namespace std;


void light_pattern() {
    int n, k, x;
    cin >> n >> k >> x;


    int p, s, b;            // p: number of patterns,
    uint16_t q = 0x00;      // q: desired pattern
    p = n / k;

    for (int i = 1; i <= k; i++) {
        q |= (x & 1)<<(k-i);
        x >>= 1;
    }

    vector<uint16_t> bulbs_state(p);
    for (int i = 0; i < p; i++) {
        s = 0;              // s to store the bulb state
        for (int j = 0; j < k; j++) {
            cin >> b;
            if (b == 1) s |= 1 << j;
        }
        bulbs_state[i] = s;
    }

    /*
    Go through the blocks from left to right. Is there a recursive relationship between the number
    of operations needed to get blocks 1..i to have the right patterns and the number of operations
    needed to get blocks 1..i-1 to have the right patterns. If so, you could do DP. If not, why
    not, and how could it be fixed? This should point you into the right direction.
    */

    // Compute the diff state of each pattern with the desired one. The int represent the number of
    // different bulbs at each of the patterns.
    vector<int> diff_state(p, 0);
    for (int i = 0; i < p; i++) {
        int diff = bulbs_state[i] ^ q;
        for (int j = 0; j < k; j++) {
            if ((diff & 1<<j) != 0) diff_state[i]++;
        }
    }

    // Compute the accumulated in case the bulbs have been changed one by one or by block all the
    // previous ones
    vector<int> values_individual(p), values_block(p);
    values_individual[0] = diff_state[0];
    values_block[0] = k - diff_state[0] + 1;
    for (int i = 1; i < p; i++) {
        values_individual[i] = min(values_individual[i-1], values_block[i-1]) + diff_state[i];
        values_block[i] = min(values_block[i-1] + k - diff_state[i],
                            values_individual[i-1] + k - diff_state[i] + 2);
    }

    cout << min(values_individual[p-1], values_block[p-1]) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        light_pattern();
    }
}
