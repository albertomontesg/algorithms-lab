
#include <vector>
#include <iostream>
#include <limits>
#include <stdlib.h>

using namespace std;

// Implementation in O(n)

void deck_of_cards(){
    long n; cin >> n;
    long k; cin >> k;

    vector<long> values(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    long i_r = 0, j_r = 0;
    long start = 0, end = 0;
    long sum = values[0];
    long min_value = abs(k-sum);

    while (start < n) {
        if (sum <= k) {
            if (end < n-1) {
                sum += values[++end];
            } else { break; }
        } else {
            sum -= values[start++];
        }
        if (abs(k-sum) < min_value) {
            min_value = abs(k-sum);
            i_r = start;
            j_r = end;
        }
    }

    cout << i_r << ' ' << j_r << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        deck_of_cards();
    }
}
