#include <vector>
#include <iostream>

using namespace std;

void do_sum(){
    int n; cin>> n;
    float sum = 0.0;
    float sumant;
    for (int i =0; i < n; i++) {
        cin >> sumant;
        sum += sumant;
    }

    cout << sum << endl;
}

int main() {
    int T; cin >> T;
    for (int t=0; t < T; t++){
        do_sum();
    }
}
