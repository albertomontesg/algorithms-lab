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

    // Calculate the result
    int counter = 0;
    for (int i =0; i < n; i++){
        int sum = 0;
        for (int j = i; j < n; j++){
            if (i > 0)
                sum = partial_sum[j] - partial_sum[i-1];
            else
                sum = partial_sum[j]

            if (sum%2 == 0)
                counter++;
        }
        cout << counter << endl;
    }
}

int main() {
    int T; cin >> T;
    for (int t=0; t < T; t++){
        do_test();
    }
}
