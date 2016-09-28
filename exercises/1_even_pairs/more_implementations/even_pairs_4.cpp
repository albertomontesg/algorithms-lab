#include <vector>
#include <iostream>

using namespace std;

void do_test(){
    int n; cin >> n;
    vector<int> bits(n);
    for (int i =0; i < n; i++)
        cin >> bits [i];

    // Precompute Si's
    vector<int> partial_sum(n);
    partial_sum[0] = bits[0];
    for (int i = 1; i < n; i++) {
        partial_sum[i] = partial_sum[i-1] + bits[i];
    }

    vector<int> evens(n), odds(n);
    evens[0] = 0; odds[0] = 0;
    if (bits[0] == 0)
        evens[0] = 1;
    else
        odds[0] = 1;
    for (int i = 1; i < n; i++) {
        evens[i] = events[i-1];
        odds[i] = odds[i-1];
        if (partial_sum[i] % 2 == 0)
            evens[i]++;
        else
            odds[i]++;
    }

    // Calculate the result
    int counter = 0;
    if (bits[0] == 0)
        counter++;
    for (int i =1; i < n; i++){
        if (partial_sum[i] % 2 == 0)
            counter += evens[i-1];
        else
            counter += odds[i-1];
    }
    cout << counter << endl;
}

int main() {
    int T; cin >> T;
    for (int t=0; t < T; t++){
        do_test();
    }
}
