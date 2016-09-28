#include <vector>
#include <iostream>

using namespace std;

void compute_dominoes_falling(){
    int n; cin >> n;
    vector<unsigned long int> dominoes_height(n);
    for (int i =0; i < n; i++)
        cin >> dominoes_height [i];

    int max = 1;

    for (int i = 0; i < n; i++) {
        if (i + dominoes_height[i] > max)
            max = i + dominoes_height[i];
        else if (max == i + 1)
            break;
    }
    if (max > n)
        max = n;

    cout << max << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        compute_dominoes_falling();
    }
}
